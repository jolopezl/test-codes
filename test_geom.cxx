#include <iostream>

int main()
{
    int kNlayer = 6;
    int kNstack = 5;

    for (int sector = 0; sector < 18; ++sector)
    // for (int cid = 0; cid<kNlayer*kNstack; ++cid)
    {
        for (int cid = 0; cid < kNlayer * kNstack; ++cid)
        //    for (int sector=0; sector<18; ++sector)
        {
            int id = cid % (kNlayer * kNstack);
            int stack = id / kNlayer;
            int stacko2 = (id % (kNlayer * kNstack)) / kNlayer;
            if (stack != stacko2) {
                std::cout << "wrong stack number " << stack << ", " << stacko2 << std::endl;
                return 1;
            }
            int layer = id % kNlayer;
            int det = layer + stack * kNlayer + sector * kNlayer * kNstack;
            std::cout << "chamber id " << cid << ", id " << id << ", stack " << stack << ", layer " << layer << ", sector " << sector << ", det " << det << std::endl;
        }
    }
    return 0;
}
