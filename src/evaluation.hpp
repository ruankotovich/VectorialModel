#ifndef __EVALUATION__
#define __EVALUATION__
#include "docollection.hpp"
#include "query.hpp"
#include <queue>
#include <algorithm>
#include <set>

double precisionR(Query query, 
    std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, QueryComparator_t> documents, 
    const double R, double alfa) {

    if(R <= documents.size() && R <= query.docsByRelevance.size()) {
        std::set<int> relevantDocuments;
        int k = 0;
        while (!query.docsByRelevance.empty() && k < R) {
            relevantDocuments.insert(std::move(const_cast<int&>(query.docsByRelevance.top().first)));
            query.docsByRelevance.pop();
            ++k;
        }

        double score = 0, irrelevantCount = 0;
        alfa += R;

        std::pair<int, double> currentDoc;
        for(int i = 0; i < R; ++i) {
            currentDoc = documents.top();

            if(relevantDocuments.find(currentDoc.first) != relevantDocuments.end()) {
                score += 1.0f - (irrelevantCount)/alfa;
            }
            else ++irrelevantCount;

            documents.pop();
        }

        return score/R;
    }
    
    return 0;
}


double pArroba(Query query, std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, QueryComparator_t> documents, double K) { 
    if(K > documents.size()) {
        return 0;
    }
    
    std::set<int> relevantDocuments;
    while (!query.docsByRelevance.empty()) {
        relevantDocuments.insert(std::move(const_cast<int&>(query.docsByRelevance.top().first)));
        query.docsByRelevance.pop();
    }

    int relevantsFound = 0;
    std::pair<int, double> currentDoc;
    for(int i = 0; i < K; ++i) {
        currentDoc = documents.top();

        if(relevantDocuments.find(currentDoc.first) != relevantDocuments.end()) {
            ++relevantsFound;
        }

        documents.pop();
    }

    return relevantsFound/K;
}
#endif
