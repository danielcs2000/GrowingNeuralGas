
#include "../GNG/gng.h"
#include "../PreProcessor/Preprocessor.h"


int main(int argc, char* argv[]){

    Preprocessor preprocessor;
    preprocessor.readImage(argv[1]);
    preprocessor.run();

    Position<int>* inputData = preprocessor.getBorderPoints();
    int n = preprocessor.getNumberPoints();

    GNG gng(inputData, n);
    GraphDrawer<int,int> graphDrawer;
    graphDrawer.readFromFile(argv[1]);
    gng.setGraphDrawer(graphDrawer);
    gng.train(10000);

    return 0;
}
