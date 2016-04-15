//
// Created by Dylan on 13/04/2016.
//

#ifndef LDA_LDA_H
#define LDA_LDA_H

#include <map>
#include <vector>
#include <set>
#include <string>

struct document {
    std::map<int,int> wordCounts;
    int count;
    int uniqueCount;
};

struct doc_corpus {
    std::vector<document> docs;
    int numTerms;
    int numDocs;
};

struct suff_stats {
    std::vector<std::vector<double>> classWord;
    std::vector<double> classTotal;
    double alphaSS;
    int numDocs;
};

class lda {

public:
    // Variables
    doc_corpus corpus;

    int numTopics;
    int numDocs;
    int numTerms;

    std::vector<std::vector<double>> logProbW;
    double alpha;

    double likelihood;

    // Functions
    void train(int num_topics);
    void writeParams(std::string folder_path);

    // Constructor
    lda(doc_corpus& corp);

private:
    // Variables
    std::vector<std::vector<double>> varGamma;
    std::vector<std::vector<std::vector<double>>> phi;

    // Functions
    void randomSSInit(suff_stats& ss);
    void zeroSSInit(suff_stats& ss);
    void mle(suff_stats& ss, bool optAlpha);
    double doc_e_step(document const& doc, suff_stats& ss, std::vector<double>& var_gamma,
                      std::vector<std::vector<double>>& phi);
    double inference(document const& doc, std::vector<double>& var_gamma,
                     std::vector<std::vector<double>>& phi);
    double compute_likelihood(document const& doc, std::vector<double>& var_gamma,
                              std::vector<std::vector<double>>& phi);
    void writeBetaToFile(std::string folder_path);
    void writeAlphaToFile(std::string folder_path);
    void writeGammaToFile(std::string folder_path);
};


#endif //LDA_LDA_H
