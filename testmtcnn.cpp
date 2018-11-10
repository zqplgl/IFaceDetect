#include<Imtcnn.h>
#include<opencv2/opencv.hpp>
#include <iostream>
#include<time.h>

using namespace std;
using namespace cv;

void getImPath(string& picDir,vector<string>&imPath)
{
    string cmd = "find "+picDir+" -name *.jpg";
    FILE *fp = popen(cmd.c_str(),"r");
    char buffer[512];
    while(1)
    {
        fgets(buffer,sizeof(buffer),fp);
        if(feof(fp))
            break;
        buffer[strlen(buffer)-1] = 0;
        imPath.push_back(string(buffer));
    }
}

void addRectangle(cv::Mat &img,const vector<BoundingBox> &res)
{
	for (int k = 0; k < res.size(); k++)
	{
        cv::rectangle(img, cv::Point(res[k].x1, res[k].y1), cv::Point(res[k].x2, res[k].y2), cv::Scalar(0, 255, 255), 2);
        for(int i = 0; i < 5; i ++)
            cv::circle(img, cv::Point(res[k].points_x[i], res[k].points_y[i]), 2, cv::Scalar(0, 255, 255), 2);
	}
}


int main()
{
    string model_dir = "/home/zqp/install_lib/models/";
    IObjZoneDetect *detector = CreateObjZoneMTcnnDetector(model_dir);

    vector<float> confidence = { 0.5,0.7,0.7 };

    string picDir = "/home/zqp/pic/face/";
    vector<string> imPath;
    getImPath(picDir,imPath);

    if(!imPath.size())
        return 0;

    for(int i=0; i<imPath.size(); ++i)
    {
        string file = imPath[i];
        string picName = file.substr(file.find_last_of("/")+1);

        cv::Mat im = cv::imread(file);

        vector<BoundingBox> faceinfos;

        clock_t start,end;
        start = clock();
        detector->detection(im,confidence,faceinfos);
        end = clock();
        cout<<picName<<"**********detect cost time: "<<(double(end-start)/CLOCKS_PER_SEC)*1000<<" ms"<<endl;

        addRectangle(im,faceinfos);
        cv::imshow("test", im);
        cv::waitKey();

    }
}
