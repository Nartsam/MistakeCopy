#include"codec.h"
#include<fstream>
#include<iostream>
#include<QBitmap>
#include<QTextEdit>
#include<QPainter>
#include<QPainterPath>

bool mcopy(const QString &src, const QString &dst) {
	QByteArray b_src=src.toLocal8Bit();
	const char* source_dir=b_src.data();
	QByteArray b_dst=dst.toLocal8Bit();
	const char* destination_dir=b_dst.data();
    std::ifstream infile(source_dir, std::ios::in | std::ios::binary);
    if (!infile.is_open()) {
        std::cout<<"Error: Open File: "<<source_dir<<" Failed"<<std::endl;
        return false;
    }
    std::ofstream outfile(destination_dir, std::ios::out | std::ios::binary);
    if (!outfile.is_open()) {
        std::cout<<"Error: Open File: "<<destination_dir<<" Failed"<<std::endl;
        infile.close();
        return false;
    }
    const int FLUSH_NUM = 1024 * 1024; //Buffer Size: 1M
    char* ch = new(std::nothrow)char[FLUSH_NUM];
    if (ch == NULL) {
        std::cout<<"Error: Memory Alloc Failed!"<<std::endl;
        infile.close(); outfile.close();
        return false;
    }
    while (!infile.eof()) {
        infile.read(ch, FLUSH_NUM); outfile.write(ch, infile.gcount());
    }
    delete[]ch; //release
    infile.close(); outfile.close();
    return true;
}
//QPixmap RoundPixmap(const QPixmap &src,int radius){
//    if(src.isNull()) return QPixmap();
//	if(radius==-1) radius=src.width()/2;
//    QSize size(2*radius,2*radius);
//    QBitmap mask(size); QPainter painter(&mask);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform);
//    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
//    painter.setBrush(QColor(0, 0, 0));
//    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);
//    QPixmap image=src.scaled(size); image.setMask(mask);
//    return image;
//}
QPixmap RoundPixmap(const QPixmap &src,int radius){
    if(src.isNull()) return QPixmap();
	if(radius==-1) radius=src.width();
	QPixmap pixmap(radius,radius);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	QPainterPath path; path.addEllipse(0, 0, radius, radius);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, radius, radius, src);
	return pixmap;
}
QString to_plain_text(const QString &html){
	QTextEdit translater; translater.setHtml(html);
	return translater.toPlainText();
}
QSize ScaledImageSize(int image_width,int image_height,int editor_width,int editor_height){
	int screen_area = 1920*1080;
	double factor=6.0;
	if(qMax(image_height,image_width)>500) factor=5.0;
	if(qMax(image_height,image_width)>700) factor=3.0;
	if(qMax(image_height,image_width)>1080) factor=2.0;
	if(qMax(image_height,image_width)>2000) factor=1.2;
    double ratio = editor_width * editor_height * factor / screen_area;
    return QSize(image_width * ratio, image_height * ratio);
}



/*
  Methods Below Completed by Ge Chang
*/

// 检查Question是否有效,如text字段非空,任何字段不包含QString:SptorStr等
bool CheckQuestionValidity(const Question &Q)
{
    return !Q.get_text().isEmpty() && !Q.get_text().contains(SptorStr)
            && !Q.get_correction().contains(SptorStr) && !Q.get_answer().contains(SptorStr)
            && !Q.get_notes().contains(SptorStr);
}
// 在QuestionList中进行搜索, reuslt_index中的搜索结果按相关性排序, 只记录索引
// Generated by ChatGPT
void SearchQuestionByString(const QString &str, std::vector<int> &result_index)
{
    result_index.clear();

    // A map to keep track of the relevance score for each question index
    std::map<int, int> relevance;

    // Iterate through each question in QuestionList
    for (int i = 0; i < (int)QuestionList.size(); ++i) {
        const auto &question = QuestionList[i];

        // Count the number of occurrences of the search string in each field of the question
        int count = 0;
        count += to_plain_text(question.get_text()).count(str);
        count += to_plain_text(question.get_correction()).count(str);
        count += to_plain_text(question.get_answer()).count(str);
        count += to_plain_text(question.get_notes()).count(str);

        // If the search string appears in the question, add the relevance score to the map
        if (count > 0) {
            relevance[i] = count;
        }
    }

    // Sort the relevance map in descending order by value (relevance score)
    std::multimap<int, int, std::greater<int>> sorted_relevance;
    for (const auto &entry : relevance) {
        sorted_relevance.insert(std::make_pair(entry.second, entry.first));
    }

    // Copy the sorted question indices to the result vector
    for (const auto &entry : sorted_relevance) {
        result_index.push_back(entry.second);
    }
}
// 在QuestionList中按标签进行搜索
// Generated by ChatGPT
void SearchQuestionByTags(const QStringList &tags, std::vector<int> &result_index)
{
    result_index.clear();
    // Iterate through each question in QuestionList
    for (int i = 0; i < (int)QuestionList.size(); ++i) {
        const auto &question = QuestionList[i];

        // Get the tags for the current question
        const QStringList &question_tags = question.get_tags();

        // Check if the current question has all the specified tags
        bool has_all_tags = true;
        for (const auto &tag : tags) {
            if (!question_tags.contains(tag)) {
                has_all_tags = false;
                break;
            }
        }

        // If the current question has all the specified tags, add its index to the result vector
        if (has_all_tags) {
            result_index.push_back(i);
        }
    }
}

// Generated by ChatGPT
double QuestionSimilarity(const Question &q1, const Question &q2)
{
    QString s1 = to_plain_text(q1.get_text());
    QString s2 = to_plain_text(q2.get_text());

    int m = s1.length();
    int n = s2.length();

    if (m == 0 || n == 0) {
        return 0.0;
    }

    // Compute the length of the longest common subsequence using dynamic programming
    QVector<QVector<int>> dp(m+1, QVector<int>(n+1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = qMax(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    // Compute the similarity score as the ratio of the length of the LCS to the length of the longer question
    double lcs_length = dp[m][n];
    double max_length = qMax(m, n);

    return lcs_length / max_length;
}


// 在QuestionList中查找相似问题
// Generated by ChatGPT
void SearchQuestionByQuestion(const Question &q, std::vector<int> &result_index)
{
    result_index.clear();

    // Iterate through each question in QuestionList
    for (int i = 0; i < (int)QuestionList.size(); ++i) {
        const auto &question = QuestionList[i];

        // Compute the similarity score between the current question and the query question
        double similarity_score = QuestionSimilarity(q, question);
		if(similarity_score==1.0) continue; // CANNOT INCLUDE INSELF
        // If the similarity score is above some threshold, add the index of the current question to the result vector
        if (similarity_score > 0.2) {
            result_index.push_back(i);
        }
    }
}
