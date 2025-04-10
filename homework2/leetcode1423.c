#include "leetcode1423.h"

/*
函数名：MaxScore
功能：  计算可获得的最大点数
输入：  cardPoints: 卡牌的分数列表，1 <= cardPoints[i] <= 10^4
        cardPointsSize: 分数列表的大小，1 <= cardPoints.length <= 10^5
        numCard: 拿numCard张卡牌，numCard < cardPointsSize。（力扣原题参数为k，但为避免参数含义模糊，改为numCard）
*/
int MaxScore(int* cardPoints, int cardPointsSize, int numCard)
{
    int score = 0;
    for (int i = 0; i < numCard; i++) { // 计算开头numCard张卡牌的总分
        score += cardPoints[i];
    }
    int maxScore = score;
    for (int i = 0; i < numCard; i++) { // 替换一张卡牌，计算新的总得分，并记录最大值
        score -= cardPoints[numCard - 1 - i];
        score += cardPoints[cardPointsSize - 1 - i];
        if (score > maxScore) {
            maxScore = score;
        }
    }

    return maxScore;
}