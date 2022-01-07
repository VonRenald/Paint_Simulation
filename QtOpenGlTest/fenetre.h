#ifndef FENETRE_H
#define FENETRE_H

#include <helper.h>

#include <QWidget>

class Fenetre : public QWidget
{
public:
    Fenetre();
private:
    Helper helper;
};

#endif // FENETRE_H
