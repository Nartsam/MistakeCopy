#include"mtextedit.h"
#include<iostream>
#include<QFileInfo>
#include<QImageReader>
#include<QMimeData>
#include<QDir>
#include<QMessageBox>
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
QString CopyImageToData(const QString &src_url){
	QString src_path=QStringList(src_url.split(":///")).back(); //get path from url
	QString dst_name(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
	QDir dst_dir(DataDir"image\\");
	if(!dst_dir.exists()){
		if(!dst_dir.mkdir(dst_dir.absolutePath())){
			std::cout<<"Error: Create Image Dir Failed"<<std::endl;
			return "";
		}
	}
	QString src_name(QFile(src_path).fileName());
	QStringList src_name_list=src_name.split('.');
	QString dst_path(DataDir"image\\"+dst_name+"."+src_name_list.back());
	//std::cout<<"Info: Create Image Name: "<<dst_path.toStdString()<<std::endl;
	if(QFile(dst_path).exists()) return "";
	if(!mcopy(src_path,dst_path)){
		std::cout<<"Error: Copy Image Failed"<<std::endl;
		return "";
	}
	return dst_path;
}
void MTextEdit::dropImage(const QUrl &url, const QImage &image){
	if(!image.isNull()){
		QTextImageFormat scaled_image;
		QString new_path=CopyImageToData(url.toString());
		if(new_path.isEmpty()){
			QMessageBox::warning(this,"啊哦","复制图片时出错了! 稍后再试吧");
			return;
		}
		scaled_image.setName(new_path);
		QSize scaled_size=ScaledImageSize(image.width(),image.height(),this->width(),this->height());
		scaled_image.setWidth(scaled_size.width());
		scaled_image.setHeight(scaled_size.height());
		//document()->addResource(QTextDocument::ImageResource, url, scaled_image);
		textCursor().insertImage(scaled_image);
	}
	else{
		QMessageBox::warning(this,"啊哦","无法解析这张图片, 换一张试试吧");
	}
}
void MTextEdit::dropTextFile(const QUrl &url){
	QFile file(url.toLocalFile());
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		textCursor().insertText(file.readAll());
}
