#ifndef CODEC_H
#define CODEC_H

#include<QSize>
#include<QPixmap>
#include"question.h"
#define TITLE_TEXT(STR) "<h2>" STR "</h2>"

bool mcopy(const QString &src,const QString &dst);
QPixmap RoundPixmap(const QPixmap &src,int radius=-1);
QSize ScaledImageSize(int image_width,int image_height,int editor_width,int editor_height);
bool CheckQuestionValidity(const Question &Q);
void SearchQuestionByString(const QString &str,std::vector<int> &result_index);
void SearchQuestionByTags(const QStringList &tags,std::vector<int> &result_index);
void SearchQuestionByQuestion(const Question &q,std::vector<int> &result_index);

#endif // CODEC_H
