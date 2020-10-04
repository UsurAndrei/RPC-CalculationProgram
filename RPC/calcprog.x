struct clientData1 {
    int N;
    int array[100];
};

struct clientData2 {
    int N;
    int array[100];
};

struct clientData3 {
    double a;
    int array[100];
    int N;
};

struct returnData2 {
    int maxmin[2];
};

struct returnData3 {
    double returnArray[100];
};

program CALC_PROG {
    version CALC_VERS {
        double calcAvg(clientData1) = 1;
        returnData2 calcMaxMin(clientData2) = 2;
        returnData3 calcMult(clientData3) = 3;
    } = 1;
} = 0x23451111;
