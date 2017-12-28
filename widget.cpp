#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    showMaximized();
    int MW_width= QApplication::desktop()->availableGeometry().right()+1;
    int MW_height= QApplication::desktop()->availableGeometry().bottom()+1;
    ui->gridLayoutWidget->setGeometry(5,5,MW_width-10,MW_height-70);

    ui->GV_main->setScene(new QGraphicsScene);

    connect(ui->PB_Open,SIGNAL(clicked()),this,SLOT(Open()));
    connect(ui->PB_table,SIGNAL(clicked()),this,SLOT(GenerateTable()));
    connect(ui->PB_answers,SIGNAL(clicked()),this,SLOT(GenerateAnswers()));
    connect(ui->LW_images,SIGNAL(currentRowChanged(int)),this,SLOT(Load(int)));
    connect(ui->PB_classifier,SIGNAL(clicked(bool)),this,SLOT(GenerateClassifier()));


    folder.setNameFilters({"*.jpg"});

    SDataFrame dump("clf.csv");
    std::vector<double> Y = dump.col(0);
    std::vector<int> iY(Y.size());
    for(size_t i=0;i<Y.size();++i)
        if (Y[i]!=0) iY[i]=1;
    dump.removeColumn(0);
    clf.fit(dump,iY);    
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Open()
{
    folder.reset();
    ui->LW_images->clear();
    QStringList list = folder.entryList();
    ui->progressBar->setMaximum(folder.size());
    ui->LW_images->addItems(list);    
}
//QTime t; t.start();qDebug()<<t.elapsed();

void Widget::Load(int num)
{
    if (num!=-1)
    {

        ui->GV_main->scene()->clear();
        QString path = folder[num];
        QImage image(path);

        SMainComponents mc(image);
        SMatrix first(image,mc.first());
        SThreshold<BINARY> bin;
        SSegmentationMap map(bin.bypass(first));
        map.combine(7000);

        SImageDescriptor master(image,map);
        master.addFeatures(new SHistogram());
        master.addComponent("B",S::Blue());
        SDataFrame X=master.run();
        std::vector<int> predictions = clf.predict(X);
        std::vector<int> segments = map.IDs();

        assert(predictions.size()==segments.size());

        std::vector<int> skin;
        for (size_t i=0;i<predictions.size();++i)
            if (!predictions[i]) skin.push_back(segments[i]);
        for (size_t i=1;i<skin.size();++i)
            map.join(skin[0],skin[i]);

        map.onImage(image);

        QPixmap diagram(QPixmap::fromImage(image));
        ui->GV_main->scene()->addPixmap(diagram);

        ui->label->clear();
        ui->label->setText(folder.name(num));
    }
}

void Widget::GenerateTable()
{
    SDataFrame result;

    for(size_t i=0;i<folder.size();++i)
    {
        ui->progressBar->setValue(i);
        QImage image(folder[i]);
        SMainComponents mc(image);
        SMatrix main_plane(image,mc.first());
        SThreshold<BINARY> bin;
        SSegmentationMap map(bin.bypass(main_plane));
        map.combine(7000);

        SImageDescriptor master(image,map);

        master.addFeatures(new SHistogram());
        master.addFeatures(new SAdjacencyMatrix());

        master.addComponent("R",S::Red());
        master.addComponent("G",S::Green());
        master.addComponent("B",S::Blue());
        master.addComponent("H",S::Hue());
        master.addComponent("S",S::Saturation());
        master.addComponent("V",S::Value());
        master.addComponent("Fm",mc.first());
        master.addComponent("Sm",mc.second());
        master.addComponent("Tm",mc.third());

        result.vstack(master.run(folder.name(i).toStdString()+"_"));

    }
    ui->progressBar->reset();

    result.toCSV("result.csv");
    ui->label->clear();
    ui->label->setText("result.csv");
}

void Widget::GenerateAnswers()
{
    ui->label->clear();

    Content markup_folder;
    markup_folder.setNameFilters({"*.bmp"});
    markup_folder.reset();

    if (markup_folder.size()==folder.size())
    {
        SDataFrame result;
        for(size_t i=0;i<folder.size();++i)
        {
            ui->progressBar->setValue(i);
            QString path = folder[i];
            QImage image(path);
            SMainComponents mc(image);
            SMatrix first(image,mc.first());
            SThreshold<BINARY> bin;
            SSegmentationMap map(bin.bypass(first));
            map.combine(7000);

            QImage markup(markup_folder[i]);
            SImageDescriptor master(markup,map);
            master.addComponent("",S::Lasy());
            master.addFeatures(new STeacher());

            QString name=markup_folder.name(i)+"_";
            result.vstack(master.run(name.toStdString()));

        }
        ui->progressBar->reset();
        result.toCSV("answers.csv");
        ui->label->setText("answers.csv");
    }
    else
    {
       ui->label->setText("Ошибка");
    }
}

void Widget::GenerateClassifier()
{
    ui->label->clear();

    Content markup_folder;
    markup_folder.setNameFilters({"*.bmp"});
    markup_folder.reset();

    if (markup_folder.size()>0)
    {
        SDataFrame result,answers;
        for(size_t i=0;i<folder.size();++i)
        {
            ui->progressBar->setValue(i);
            QImage image(folder[i]);
            SMainComponents mc(image);
            SMatrix main_plane(image,mc.first());
            SThreshold<BINARY> bin;
            SSegmentationMap map(bin.bypass(main_plane));
            map.combine(7000);

            SImageDescriptor master(image,map);
            master.addFeatures(new SHistogram());
            master.addComponent("B",S::Blue());
            result.vstack(master.run(folder.name(i).toStdString()+"_"));

            QImage markup(markup_folder[i]);
            SImageDescriptor markup_master(markup,map);
            markup_master.addComponent("",S::Lasy());
            markup_master.addFeatures(new STeacher());
            QString name=markup_folder.name(i)+"_";
            answers.vstack(markup_master.run(name.toStdString()));

        }
        ui->progressBar->reset();
        answers+=result;
        answers.toCSV("clf.csv");

        ui->label->setText("clf.csv");
    }
    else
    {
        ui->label->setText("Ошибка");
    }
}
