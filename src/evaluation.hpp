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
        while (!query.docsByRelevance.empty()) {
            relevantDocuments.insert(std::move(const_cast<int&>(query.docsByRelevance.top().second)));
            query.docsByRelevance.pop();
        }

        double score = 0, irrelevantCount = 0;
        alfa += R;

        std::pair<int, int> currentDoc;
        for(int i = 0; i < R; ++i) {
            currentDoc = documents.top();

            if(relevantDocuments.find(currentDoc.first) != relevantDocuments.end()) {
                score = 1 - (i - 1 - irrelevantCount)/alfa;
            }
            else ++irrelevantCount;

            documents.pop();
        }

        return score/R;
    }
    
    return 0;
}

#endif
