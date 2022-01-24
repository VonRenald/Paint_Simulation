#include "MainWindow.h"
MainWindow::MainWindow()
{
	this->setMinimumSize(375+50, 300+50);
	widget = new QtWidgetsVS(this);

	QMenu* menuFichier = menuBar()->addMenu("&Fichier");
	QAction* acctionNew = new QAction("&New", this);
	QAction* acctionSav = new QAction("&Sav", this);
	QAction* acctionQuitter = new QAction("&Quitter", this);
	menuFichier->addAction(acctionNew);
	menuFichier->addAction(acctionSav);
	menuFichier->addAction(acctionQuitter);

	connect(acctionNew, &QAction::triggered, this, &MainWindow::creatNewCanvas);
	connect(acctionSav, &QAction::triggered, this, &MainWindow::saveTexture);
	connect(acctionQuitter, &QAction::triggered, this, &QMainWindow::close);
}
MainWindow::~MainWindow()
{

}
void MainWindow::resizeEvent(QResizeEvent* event)
{
	widget->setFixedSize(event->size());
}
void MainWindow::creatNewCanvas()
{
	bool ok;
	int w, h;
	w = QInputDialog::getInt(this, tr("new canvas"),
		tr("X size:"), 255, 1, 2147483647, 1, &ok);
	if (ok) {
		h = QInputDialog::getInt(this, tr("new canvas"),
			tr("Y size:"), 255, 1, 2147483647, 1, &ok);
		if (ok)
		{
			widget->newCanvas(w, h);
		}
	}
}
void MainWindow::saveTexture()
{
	widget->saveTexture();
}