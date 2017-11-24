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
    connect(ui->LW_images,SIGNAL(currentRowChanged(int)),this,SLOT(Load(int)));

    folder.setNameFilters({"*.jpg"});
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Open()
{
    folder.reset();
    ui->LW_images->clear();
    ui->LW_images->addItems(folder.entryList());
}

void Widget::Load(int num)
{
    if (num!=-1)
    {
        ui->GV_main->scene()->clear();

        QImage image(folder[num]);
        SMainComponent formula(image);
        formula.useComponent(1);
        SMatrix main_plane(image,formula);
        SSegmentationMap map(main_plane);
        int threshold=OtsuThreshold(map.scale(0,255));
        Threshold(map,threshold);
        map.combineSmallWithLarge(5000);
        QPixmap diagram(QPixmap::fromImage(map.toImage()));



//        std::vector<int> v = postThresholdSegmentation(map);
//        int id=0;
//        for (int i=0;i<int(v.size());++i)
//            if (v[id]<v[i]) id=i;

        //QPixmap diagram(QPixmap::fromImage(map.colorDiagram()));
//        QPixmap diagram(QPixmap::fromImage(map.segmentationDiagram()));
        //QPixmap diagram(QPixmap::fromImage(takeSegment(main_plane,map,id).colorDiagram()));

        ui->GV_main->scene()->addPixmap(diagram);
    }


    /*
    int puzzle_size=20;
    const int col_lim=image.width()/puzzle_size;
    const int row_lim=image.height()/puzzle_size;
    SGrid<QRect> grid(puzzle_size,puzzle_size);
    SMatrix mat(col_lim,row_lim);
    QTime clock;
    for(int r=0;r<row_lim;++r)
    {
        clock.start();//
        for(int c=0;c<col_lim;++c)
        {
             SMatrix plane(image.copy(grid(c,r)));
             SAdjacencyMatrix AM(plane);
             mat(c,r)=AM.averageBrightness();
        }
        qDebug("Time elapsed: %d ms", clock.elapsed());
    }
    QPixmap diagram(QPixmap::fromImage(mat.colorDiagram()));
    ui->GV_main->scene()->addPixmap(diagram);*/
}
