#include "MainWindow.h"
MainWindow::MainWindow()
{
	this->setMinimumSize(375, 300);
	widget = new QtWidgetsVS(this);

	QMenu* menuFichier = menuBar()->addMenu("&Fichier");
	QAction* acctionQuitter = new QAction("&Quitter", this);
	menuFichier->addAction(acctionQuitter);

	connect(acctionQuitter, &QAction::triggered, this, &QMainWindow::close);
}
MainWindow::~MainWindow()
{

}
void MainWindow::resizeEvent(QResizeEvent* event)
{
	widget->setFixedSize(event->size());
}