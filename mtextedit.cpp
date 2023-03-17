#include "mtextedit.h"
#include<QFileInfo>
#include<QImageReader>
#include<QMimeData>
#include"codec.h"
MTextEdit::MTextEdit(QWidget *parent):QTextEdit(parent){}
bool MTextEdit::canInsertFromMimeData(const QMimeData *source) const{
    return source->hasImage() || source->hasUrls() || 
			QTextEdit::canInsertFromMimeData(source);
}
void MTextEdit::insertFromMimeData(const QMimeData *source){
    if (source->hasImage()) {
        static int i = 1;
        QUrl url(QString("dropped_image_%1").arg(i++));
        dropImage(url, qvariant_cast<QImage>(source->imageData()));
    }
    else if (source->hasUrls()) {
        foreach (QUrl url, source->urls()) {
            QFileInfo info(url.toLocalFile());
            if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
                dropImage(url, QImage(info.filePath()));
            else
                dropTextFile(url);
        }
    }
    else {
        QTextEdit::insertFromMimeData(source);
    }
}
void MTextEdit::dropImage(const QUrl &url, const QImage &image){
    if (!image.isNull()) {
		QImage scaled_image=image.scaled(
				ScaledImageSize(image.width(),image.height(),this->width(),this->height()));
        document()->addResource(QTextDocument::ImageResource, url, scaled_image);
        textCursor().insertImage(url.toString());
    }
}
void MTextEdit::dropTextFile(const QUrl &url){
    QFile file(url.toLocalFile());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        textCursor().insertText(file.readAll());
}
