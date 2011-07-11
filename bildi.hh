#ifndef BILDI_HH
#define BILDI_HH

#include <QMainWindow>
#include <QtGui>

class Bildi : public QMainWindow
{
    Q_OBJECT
public:
	explicit Bildi(QWidget *parent = 0, QStringList* args = 0);
	QStringList* args;

private:
	QLabel* imageLabel;
	QScrollArea* imageScrollArea;
	bool fitToWindow;
	bool vollbild;
	int pos;
	QStringList imagePaths;
	void keyPressEvent(QKeyEvent* e);
	void draw();
	//QImage image;
	QPixmap pixmap;
	void windowPos();
	/*QPixmap nextpixmap;
	QList<QPixmap> pili;*/

signals:

public slots:

};

#endif // BILDI_HH
