//
// Created by ly on 2018/8/15.
//

#include <iostream>

class StableMatching{
private:
    int **manPreference;
    int **womenPreference;
    int numberOfPerson;
public:
    StableMatching(){}
    void init(int **manPreference, int **womenPreference, int numberOfPerson){
        this->manPreference = manPreference;
        this->womenPreference = womenPreference;
        this->numberOfPerson = numberOfPerson;
    }

    void run(){
        int queueMan[numberOfPerson];
        int queueWoman[numberOfPerson];
        int womanNo = -1;
        //init
        for (int i = 0; i < numberOfPerson; ++i) {
            queueMan[i] = -1;
            queueWoman[i] = -1;
        }

        while(true){
            //check
            auto test = -1;
            for (int i = 0; i < numberOfPerson; ++i) {
                if(queueMan[i]==-1)
                    test = i;
            }

            if(test==-1)
                break;

            for (int i = 0; i < numberOfPerson; ++i) {
                if(queueMan[i]!=-1)
                    continue;

                for (int j = 0; j < numberOfPerson; ++j) {
                    for (int k = 0; k < numberOfPerson; ++k) {
                        if(manPreference[i][k] == j){
                            womanNo = k;
                            break;
                        }
                    }

                    //woman is free
                    if(queueWoman[womanNo]==-1){
                        queueMan[i] = womanNo;
                        queueWoman[womanNo] = i;
                        break;
                    }//not free
                    else if(womenPreference[womanNo][i] < womenPreference[womanNo][queueWoman[womanNo]]){
                        queueMan[queueWoman[womanNo]] = -1;
                        queueMan[i] = womanNo;
                        queueWoman[womanNo] = i;
                        break;
                    }else{
                        continue;
                    }
                }
            }
        }

        //print
        std::cout << "woman for man:";
        for (int i = 0; i < numberOfPerson; ++i) {
            std::cout << queueMan[i] << " ";
        }
        std::cout << std::endl;

        std::cout << "man for woman:";
        for (int i = 0; i < numberOfPerson; ++i) {
            std::cout << queueWoman[i] << " ";
        }
    }
};

int main(){
    int numberOfPerson;
    int **manPreference;
    int **womenPreference;
    StableMatching stableMatching;
    std::cout << "enter number of persons:" << std::endl;
    std::cin >> numberOfPerson;

    //init the array
    manPreference = new int *[numberOfPerson];
    womenPreference = new int *[numberOfPerson];
    for (int i = 0; i < numberOfPerson; ++i) {
        manPreference[i] = new int[numberOfPerson];
        womenPreference[i] = new int[numberOfPerson];
    }

    //enter the preference rank list of man
    for (int i = 0; i < numberOfPerson; ++i) {
        std::cout << "enter the preference rank of men " << i << std::endl;
        for (int j = 0; j < numberOfPerson; ++j) {
            std::cin >> manPreference[i][j];
        }
    }

    //enter the preference rank list of woman
    for (int i = 0; i < numberOfPerson; ++i) {
        std::cout << "enter the preference rank of women" << i << std::endl;
        for (int j = 0; j < numberOfPerson; ++j) {
            std::cin >> womenPreference[i][j];
        }
    }

    //calculate
    stableMatching.init(manPreference, womenPreference, numberOfPerson);
    stableMatching.run();
}

//input
/*
 * group one
 * 3
 * 0 2 1
 * 0 1 2
 * 1 0 2
 *
 * 1 0 2
 * 2 0 1
 * 1 2 0
 *
 * group two
 * 3
 * 0 2 1
 * 1 0 2
 * 2 1 0
 *
 * 1 2 0
 * 2 0 1
 * 0 2 1
 *
 * group three
 * 2
 * 0 1
 * 1 0
 *
 * 0 1
 * 1 0
 */

