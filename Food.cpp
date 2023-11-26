#include "Food.h"

Food::Food()
{
    QPixmap pixmap(":/images/Food.png");
    pixmap = pixmap.scaled(QSize(30, 30));
    setPixmap(pixmap);
}
