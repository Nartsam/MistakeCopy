#include"codec.h"

/*
重新计算image_width和image_height，使图像缩放后的大小在编辑框中的占比，
和图像原始大小在显示器上的占比近似相同，保持图像纵横比不变
*/
QSize ScaledImageSize(int image_width, int image_height, int editor_width, int editor_height){
	int screen_width=1920,screen_height=1080;
	// incomplete
	return QSize(image_width,image_height);
}
// 检查Question是否有效,如text字段非空,任何字段不包含QString:SptorStr等
bool CheckQuestionValidity(const Question &Q){
	//incomplete
}
// 在QuestionList中进行搜索, reuslt_index中的搜索结果按相关性排序, 只记录索引
void SearchQuestionByString(const QString &str, std::vector<int> &result_index){
	result_index.clear();
	//incomplete
}
// 在QuestionList中按标签进行搜索
void SearchQuestionByTags(const QStringList &tags, std::vector<int> &result_index){
	result_index.clear();
	//incomplete
}
// 在QuestionList中查找相似问题
void SearchQuestionByQuestion(const Question &q, std::vector<int> &result_index){
	result_index.clear();
	//incomplete
}
