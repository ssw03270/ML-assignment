#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cmath>
#include <random>

using namespace std;

vector<string> columnsName = { "ID", "Sex", "Age", "lbankssts", "rbankssts",
       "lcaudalanteriorcingulate", "rcaudalanteriorcingulate",
       "lcaudalmiddlefrontal", "rcaudalmiddlefrontal", "lcuneus", "rcuneus",
       "lentorhinal", "rentorhinal", "lfusiform", "rfusiform",
       "linferiorparietal", "rinferiorparietal", "linferiortemporal",
       "rinferiortemporal", "listhmuscingulate", "risthmuscingulate",
       "llateraloccipital", "rlateraloccipital", "llateralorbitofrontal",
       "rlateralorbitofrontal", "llingual", "rlingual", "lmedialorbitofrontal",
       "rmedialorbitofrontal", "lmiddletemporal", "rmiddletemporal",
       "lparahippocampal", "rparahippocampal", "lparacentral", "rparacentral",
       "lparsopercularis", "rparsopercularis", "lparsorbitalis",
       "rparsorbitalis", "lparstriangularis", "rparstriangularis",
       "lpericalcarine", "rpericalcarine", "lpostcentral", "rpostcentral",
       "lposteriorcingulate", "rposteriorcingulate", "lprecentral",
       "rprecentral", "lprecuneus", "rprecuneus", "lrostralanteriorcingulate",
       "rrostralanteriorcingulate", "lrostralmiddlefrontal",
       "rrostralmiddlefrontal", "lsuperiorfrontal", "rsuperiorfrontal",
       "lsuperiorparietal", "rsuperiorparietal", "lsuperiortemporal",
       "rsuperiortemporal", "lsupramarginal", "rsupramarginal", "lfrontalpole",
       "rfrontalpole", "ltemporalpole", "rtemporalpole", "ltransversetemporal",
       "rtransversetemporal", "linsula", "rinsula", "ICV" };

bool maeIsBig(double mae) {
    string fileName = "mae.txt";
    ifstream readFile;                     // 열릴 파일
    readFile.open(fileName);               // 파일 열기

    if (readFile.is_open()) {
        string line;                    
        getline(readFile, line);        
        double oldMae = stod(line);
        if (oldMae > mae) {
            readFile.close();
            cout << "new record";
            return true;
        }
        else {
            readFile.close();
            return false;
        }
    }
    else {
        readFile.close();
        cout << "new record2";
        return true;
    }
}

void saveParameta(double newMae, vector<double> featureMae, vector<int> usefulColumns, vector<vector<double>> featureMeans) {
    if (maeIsBig(newMae)) {
        string fileName = "mae.txt";
        ofstream writeFile;                     // 열릴 파일
        writeFile.open(fileName);                // 파일 열기

        if (writeFile.is_open()) {
            string text = to_string(newMae);
            writeFile.write(text.c_str(), text.size());
        }
        writeFile.close();

        fileName = "featureMae.csv";
        writeFile.open(fileName);                // 파일 열기

        if (writeFile.is_open()) {
            for (const auto& mae : featureMae) {
                string text = to_string(mae) + ", ";
                writeFile.write(text.c_str(), text.size());
            }
        }
        writeFile.close();

        fileName = "usefulColumns.csv";
        writeFile.open(fileName);                // 파일 열기

        if (writeFile.is_open()) {
            for (const auto& column : usefulColumns) {
                string text = to_string(column) + ", ";
                writeFile.write(text.c_str(), text.size());
            }
        }
        writeFile.close();

        fileName = "featureMeans.csv";
        writeFile.open(fileName);                // 파일 열기

        if (writeFile.is_open()) {
            for (const auto& means : featureMeans) {
                for (const auto& mean : means) {
                    string text = to_string(mean) + ", ";
                    writeFile.write(text.c_str(), text.size());
                }
                writeFile.write("\n", 1);
            }
        }
        writeFile.close();
    }
}

void readData(vector<double> &featureMae, vector<int> &usefulColumns, vector<vector<double>> &featureMeans) {
    string fileName = "featureMae.csv";
    ifstream readFile;                     // 열릴 파일
    readFile.open(fileName);                // 파일 열기

    if (readFile.is_open()) {
        string line;                    // 전체 문자열이 저장될 string
        getline(readFile, line);        // 전체 문자열  입력
        int strLength = 0;              // 나뉘어질 문자열의 길이

        // 쉼표 기준으로 문자열 자르기
        while (line.find(",") != string::npos) {
            strLength = line.find(",");                 // 쉼표 이전까지의 길이

            string newStr = line.substr(0, strLength);  // 쉼표 이전까지의 문자열을 새로운 문자열에 저장
            line.replace(0, strLength + 1, "");         // 쉼표 포함 이전까지의 문자열 삭제

            featureMae.push_back(stod(newStr));            // 새로운 문자열 벡터에 저장
        }
    }
    readFile.close();

    fileName = "usefulColumns.csv";
    readFile.open(fileName);                // 파일 열기

    if (readFile.is_open()) {
        string line;                    // 전체 문자열이 저장될 string
        getline(readFile, line);        // 전체 문자열  입력
        int strLength = 0;              // 나뉘어질 문자열의 길이

        // 쉼표 기준으로 문자열 자르기
        while (line.find(",") != string::npos) {
            strLength = line.find(",");                 // 쉼표 이전까지의 길이

            string newStr = line.substr(0, strLength);  // 쉼표 이전까지의 문자열을 새로운 문자열에 저장
            line.replace(0, strLength + 1, "");         // 쉼표 포함 이전까지의 문자열 삭제

            usefulColumns.push_back(stod(newStr));            // 새로운 문자열 벡터에 저장
        }
    }
    readFile.close();

    fileName = "featureMeans.csv";
    readFile.open(fileName);                // 파일 열기

    if (readFile.is_open()) {
        while (!readFile.eof()) {           // 읽을 데이터가 있으면 진행
            string line;                    // 전체 문자열이 저장될 string
            getline(readFile, line);        // 전체 문자열  입력

            if (line.find(",") == string::npos) {
                break;
            }
            vector<double> separatedLine;
            int strLength = 0;              // 나뉘어질 문자열의 길이

            // 쉼표 기준으로 문자열 자르기
            while (line.find(",") != string::npos) {
                strLength = line.find(",");                 // 쉼표 이전까지의 길이

                string newStr = line.substr(0, strLength);  // 쉼표 이전까지의 문자열을 새로운 문자열에 저장
                line.replace(0, strLength + 1, "");         // 쉼표 포함 이전까지의 문자열 삭제

                separatedLine.push_back(stod(newStr));            // 새로운 문자열 벡터에 저장

            }
            featureMeans.push_back(separatedLine);
        }
    }
    readFile.close();
}

vector<vector<string>> readFile(const string fileName) {
    ifstream readFile;                      // 열릴 파일
    readFile.open(fileName);                // 파일 열기

    vector<vector<string>> lines;           // 전체 데이터를 담을 이차원 벡터
    if (readFile.is_open()) {               // 열 수 있으면 열기
        while (!readFile.eof()) {           // 읽을 데이터가 있으면 진행
            string line;                    // 전체 문자열이 저장될 string
            getline(readFile, line);        // 전체 문자열  입력
            
            if (line.find(",") == string::npos) {
                break;
            }

            vector<string> separatedLine;   // 나뉘어질 문자열이 저장될 벡터
            int strLength = 0;              // 나뉘어질 문자열의 길이
            bool isNaN = false;             // NaN 값 체크용 변수
            
            // ID 값 제거
            if (line.find("ID") != string::npos || line.find("IXI") != string::npos) {
                line.replace(0, line.find(",") + 1, "");    // ID까지의 문자열 삭제
            }

            // 쉼표 기준으로 문자열 자르기
            while (line.find(",") != string::npos) {
                strLength = line.find(",");                 // 쉼표 이전까지의 길이

                string newStr = line.substr(0, strLength);  // 쉼표 이전까지의 문자열을 새로운 문자열에 저장
                line.replace(0, strLength + 1, "");         // 쉼표 포함 이전까지의 문자열 삭제

                separatedLine.push_back(newStr);            // 새로운 문자열 벡터에 저장
                
                if (newStr.compare("NaN") == 0) {           // NaN 값이 있을 경우 break
                    isNaN = true;
                    break;
                }
            }
            if (!isNaN) {                                   // NaN 값이 없는 경우 벡터 저장
                separatedLine.push_back(line);              // ICV 값은 쉼표가 없기에 따로 추가로 저장
                lines.push_back(separatedLine);             // 벡터에 나뉘어진 문자열 벡터 저장
            }
            
        }
        readFile.close();   // 파일 닫기
    }
    return lines;           // 전체 데이터 반환
}

void test(string fileName) {
    vector<double> featureMae;
    vector<int> usefulColumns;
    vector<vector<double>> featureMeans;
    readData(featureMae, usefulColumns, featureMeans);

    vector<vector<string>> data = readFile(fileName);
    vector<vector<double>> newData;

    bool isFirstLine = true;
    for (const auto& datum : data) {
        if (isFirstLine) { isFirstLine = false; continue; }
        vector<double> line;
        for (const auto& index : datum) {
            if (index.compare("") == 0) {
                line.push_back(0);
            }
            else {
                line.push_back(stod(index));
            }
        }
        newData.push_back(line);
    }

    vector<vector<double>> x;           // x 데이터

    for (const auto& datum : newData) {
        vector<double> xLine;
        for (int i = 1; i < datum.size(); i++) {        // 성별은 데이터에서 제외 (성별 데이터 위치 == 0)
            if (i == 1) {
                continue;
            }
            xLine.push_back(datum[i]);  // 그 외에 다른 데이터는 x에 저장
        }
        x.push_back(xLine);
    }

    int dataCount = 0;
    vector<double> mean(columnsName.size() - 3);
    vector<double> std(columnsName.size() - 3);

    // 평균 구하기
    for (const auto& datum : x) {
        for (int i = 0; i < datum.size(); i++) {
            mean[i] += datum[i];
        }
    }
    for (int i = 0; i < columnsName.size() - 3; i++) {
        mean[i] /= x.size();
    }

    // 표준편차 구하기
    for (const auto& datum : x) {
        for (int i = 0; i < datum.size(); i++) {
            std[i] += (datum[i] - mean[i]) * (datum[i] - mean[i]);
        }
    }
    for (int i = 0; i < columnsName.size() - 3; i++) {
        std[i] /= x.size();
        std[i] = sqrt(std[i]);
    }

    // StandardScaler
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[i].size(); j++) {
            x[i][j] = (x[i][j] - mean[j]) / std[j];
        }
    }

    // test 값을 이용해 각 feature 별로 나이 예측
    vector<vector<double>> finalAge;
    for (int i = 0; i < x.size(); i++) {
        vector<double> inputData;   // test의 한 줄을 inputData에 저장
        for (int j = 0; j < x[i].size(); j++) {
            inputData.push_back(x[i][j]);
        }
        double predictAge = 0;      // ㅇ{측된 나이
        double weightSum = 0;       // 가중치의 총합
        for (int j = 0; j < usefulColumns.size(); j++) {
            double weight = featureMae[j];
            weightSum += weight;
            double minDiffrent = 999;   // 가장 오차가 적은 값
            double minAge = 0;          // 그 때의 나이
            for (int z = 0; z < featureMeans.size(); z++) {
                double temp = abs(featureMeans[z][usefulColumns[j] + 1] - inputData[usefulColumns[j]]);
                if (minDiffrent > temp) {
                    minDiffrent = temp;
                    minAge = featureMeans[z][0];
                }
            }
            predictAge += minAge * weight;
        }
        predictAge /= weightSum;
        cout << predictAge << endl;
    }
}

// 랜덤하게 vector 셔플
vector<vector<double>> randomSuffle(vector<vector<double>> data) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(data.begin(), data.end(), g);

    return data;
}

int main() {
    vector<vector<string>> data = readFile("IXI_train.csv");    // 데이터 저장
    vector<vector<double>> newData;

    bool isFirstLine = true;
    for (const auto& datum : data) {
        if (isFirstLine) { isFirstLine = false; continue; }
        vector<double> line;
        for (const auto& index : datum) {
            line.push_back(stod(index));
        }
        newData.push_back(line);
    }

    newData = randomSuffle(newData);
    
    vector<vector<double>> x;           // x 데이터
    vector<double> y;                   // y 데이터

    for (const auto& datum : newData) {
        vector<double> xLine;
        for (int i = 1; i < datum.size(); i++) {        // 성별은 데이터에서 제외 (성별 데이터 위치 == 0)
            if (i == 1) {
                y.push_back(datum[i]);  // 나이 데이터는 y에 저장
                continue;
            }
            xLine.push_back(datum[i]);  // 그 외에 다른 데이터는 x에 저장
        }
        x.push_back(xLine);
    }
    
    int dataCount = 0;
    vector<double> mean(columnsName.size() - 3);
    vector<double> std(columnsName.size() - 3);

    // 평균 구하기
    for (const auto& datum : x) {
        for (int i = 0; i < datum.size(); i++) {
            mean[i] += datum[i];
        }
    }
    for (int i = 0; i < columnsName.size() - 3; i++) {
        mean[i] /= x.size();
    }

    // 표준편차 구하기
    for (const auto& datum : x) {
        for (int i = 0; i < datum.size(); i++) {
            std[i] += (datum[i] - mean[i]) * (datum[i] - mean[i]);
        }
    }
    for (int i = 0; i < columnsName.size() - 3; i++) {
        std[i] /= x.size();
        std[i] = sqrt(std[i]);
    }
    
    // StandardScaler
    for (int i = 0; i < x.size(); i++) {
        for (int j = 0; j < x[i].size(); j++) {
            x[i][j] = (x[i][j] - mean[j]) / std[j];
        }
    }

    // train test split
    vector<vector<double>> x_train;
    vector<vector<double>> x_test;
    vector<double> y_train;
    vector<double> y_test;
    int trainSize = 324;

    // x와 y의 train 분리
    for (int i = 0; i < trainSize; i++) {
        vector<double> x_trainLine;
        for (int j = 0; j < x[i].size(); j++) {
            x_trainLine.push_back(x[i][j]);
        }
        x_train.push_back(x_trainLine);
        y_train.push_back(y[i]);
    }
    // x와 y의 test 분리
    for (int i = trainSize; i < x.size(); i++) {
        vector<double> x_testLine;
        for (int j = 0; j < x[i].size(); j++) {
            x_testLine.push_back(x[i][j]);
        }
        x_test.push_back(x_testLine);
        y_test.push_back(y[i]);
    }

    // 각 나이 별로 feature 평균 저장
    vector<vector<double>> featureMeans(100, vector<double>(columnsName.size() - 2, 0));
    vector<int> ages(100);
    for (int i = 0; i < trainSize; i++) {
        int age = y_train[i];
        featureMeans[age][0] = age;
        for (int j = 0; j < x_train[i].size(); j++) {
            featureMeans[age][j + 1] += x_train[i][j];
        }
        ages[age] += 1;
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 1; j < featureMeans[i].size(); j++) {
            featureMeans[i][j] /= ages[i];
        }
    }

    // 필요없는 나이 제거 (0으로 이루어진 나이)
    for (int i = 0; i < 100; i++) {
        if (i < featureMeans.size() && featureMeans[i][0] == 0) {
            featureMeans.erase(featureMeans.begin() + i);
            i -= 1;
        }
    }

    // test 값을 이용해 각 feature 별로 나이 예측
    vector<vector<double>> finalAge;
    for (int i = 0; i < x_test.size(); i++) {
        vector<double> inputData;   // x_test의 한 줄을 inputData에 저장
        vector<double> predictAge;  // 각 feature 별로 예측 나이 저장
        for (int j = 0; j < x_test[i].size(); j++) {
            inputData.push_back(x_test[i][j]);
        }
        // 각 feature 별로 가장 오차가 적은 나이 저장
        for (int k = 1; k < columnsName.size() - 2; k++) {
            double minDiffrent = 999;   // 가장 오차가 적은 값
            double minAge = 0;          // 그 때의 나이
            for (int z = 0; z < featureMeans.size(); z++) {
                double temp = abs(featureMeans[z][k] - inputData[k - 1]);
                if (minDiffrent > temp) {
                    minDiffrent = temp;
                    minAge = featureMeans[z][0];
                }
            }
            predictAge.push_back(abs(minAge - y_test[i]));
        }
        finalAge.push_back(predictAge);
    }
    // predictAge를 바탕으로 각 feature 별로 mae 값 계산하고 사용하기 좋은 feature 탐색
    vector<double> featureMae;
    vector<int> usefulColumns;
    double minFeatureMae = 999;
    for (int i = 0; i < columnsName.size() - 3; i++) {
        double featureSum = 0;
        for (int j = 0; j < finalAge.size(); j++) {
            featureSum += finalAge[j][i];
        }
        if (featureSum / x_test.size() < 15) {
            featureMae.push_back(-1 * featureSum / x_test.size());
            usefulColumns.push_back(i);
            minFeatureMae = min(minFeatureMae, -1 * featureSum / x_test.size());
        }
    }
    // 음수가 된 fatureMae에서 가장 작은 값을 기준으로 1로 만든다
    for (int i = 0; i < featureMae.size(); i++) {
        featureMae[i] += -1 * minFeatureMae + 1;
    }

    // 
    // 
    // test 값을 이용해 각 feature 별로 나이 예측
    double finalMae = 0;
    for (int i = 0; i < x_test.size(); i++) {
        vector<double> inputData;   // test의 한 줄을 inputData에 저장
        for (int j = 0; j < x_test[i].size(); j++) {
            inputData.push_back(x_test[i][j]);
        }
        double predictAge = 0;      // 예측된 나이
        double weightSum = 0;       // 가중치의 총합
        for (int j = 0; j < usefulColumns.size(); j++) {
            double weight = featureMae[j];
            weightSum += weight;
            double minDiffrent = 999;   // 가장 오차가 적은 값
            double minAge = 0;          // 그 때의 나이
            for (int z = 0; z < featureMeans.size(); z++) {
                double temp = abs(featureMeans[z][usefulColumns[j] + 1] - inputData[usefulColumns[j]]);
                if (minDiffrent > temp) {
                    minDiffrent = temp;
                    minAge = featureMeans[z][0];
                }
            }
            predictAge += minAge * weight;
        }
        predictAge /= weightSum;
        predictAge = floor(predictAge);
        finalMae += abs(predictAge - y_test[i]);
    }
    double mae = finalMae / x_test.size();
    cout << mae << endl;

    saveParameta(mae, featureMae, usefulColumns, featureMeans);


    // test("IXI_test.csv");
    // test("COBRE_test_scz.csv");
}