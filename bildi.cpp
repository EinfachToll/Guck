#include "bildi.hh"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <QDebug>

Bildi::Bildi(QWidget *parent, QStringList* args) :
	QMainWindow(parent), args(args)
{
	srand(time(NULL));
	fitToWindow = false;
	vollbild = false;
	pos = 0;

	imageLabel = new QLabel;
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);

	imageScrollArea = new QScrollArea;
	imageScrollArea->setBackgroundRole(QPalette::Dark);
	imageScrollArea->setWidget(imageLabel);
	imageScrollArea->setWidgetResizable(fitToWindow);
	imageScrollArea->setFrameShape(QFrame::NoFrame);
	setCentralWidget(imageScrollArea);

	setWindowTitle(tr("Bildi"));

	if(args->count() == 2)
	{
		QFileInfo fileinfo(args->at(1));
		if(fileinfo.exists())
		{
			QDir dir = fileinfo.dir();
			imagePaths = dir.entryList(QDir::Files);
			for(int i=0; i<imagePaths.count(); ++i)
				imagePaths[i] = dir.absolutePath() + "/" + imagePaths.at(i);
		}

	} else
	{
		for(int i=1; i<args->count(); ++i)
			imagePaths[i] = args->at(i);
	}
	//qDebug() << imagePaths;

	/*pixmap.load(imagePaths.at(pos));
	nextpixmap.load(imagePaths.at(pos+1));
	pili << pixmap;
	pili << nextpixmap;
	qDebug() << "hihi";*/
	draw();
}

void Bildi::draw()
{
	/*QImage image(imagePaths.at(pos));
	imageLabel->setPixmap(QPixmap::fromImage(image));*/
	pixmap.load(imagePaths.at(pos));
	//pixmap = nextpixmap;
	imageLabel->setPixmap(pixmap);
	//nextpixmap.load(imagePaths.at(pos+1));
	windowPos();
}

void Bildi::windowPos()
{
	QRect rect = QApplication::desktop()->availableGeometry();

	int zugrx = rect.width() - pixmap.width();
	int zugry = rect.height() - pixmap.height();
	if(!fitToWindow || zugrx > 0 || zugry > 0)
	{
		imageLabel->adjustSize();
	}
	int posx = 0;
	int posy = 0;
	if(zugrx >= 40)
		posx = 20;
	else if(zugrx < 40 && zugrx > 0)
		posx = zugrx / 2;

	if(zugrx >= 40)
		posy = 20;
	else if(zugry < 40 && zugry > 0)
		posy = zugry / 2;

	//this->resize(1000, 800);//imageLabel->width(), imageLabel->height());
	//qDebug() << rect << posy;
	//if(!fitToWindow)
	{
		int breite;
		if(imageLabel->width() <= rect.width())
			breite = imageLabel->width();
		else
			breite = rect.width();

		int hoehe = qMin(imageLabel->height(), rect.height());
		resize(breite, hoehe);
	}
	this->move(posx, posy);

}

void Bildi::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_F)
	{
		fitToWindow = fitToWindow ? false : true;
		imageScrollArea->setWidgetResizable(fitToWindow);
		imageLabel->adjustSize();
		windowPos();
		return;
	} else

	if(e->key() == Qt::Key_V)
	{
		vollbild = vollbild ? false : true;
		if(vollbild)
		{
			//setWindowFlags(Qt::FramelessWindowHint);
			showFullScreen();
		}
		else
			showNormal();
	}

	if(e->key() == Qt::Key_Space)
	{
		pos = (pos + 1) % imagePaths.count();
		draw();
	} else

	if(e->key() == Qt::Key_Backspace)
	{
		--pos;
		if(pos < 0)
			pos = imagePaths.count() - 1;
		draw();
	} else

	if(e->key() == Qt::Key_Z)
	{
		pos = rand() % imagePaths.count();
		draw();
	} else

	if(e->key() == Qt::Key_Home)
	{
		pos = 0;
		draw();
	} else

	if(e->key() == Qt::Key_End)
	{
		pos = imagePaths.count() - 1;
		draw();
	} else

	if(e->key() == Qt::Key_Q || e->key() == Qt::Key_Escape)
		close();

}
