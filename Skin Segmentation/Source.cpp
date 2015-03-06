#include <opencv2\opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

/*--------------- SKIN SEGMENTATION ---------------*/
int main() {
	
	/*-----the first batch of this code is about extracting hue and saturation values from samples to a text file-----*/
	/*
	char name[60];
	Mat srcHSV;
	Mat srcFilter;
	ofstream dataset_file;
	int i = 1;
	while (i < 7)
	{
		sprintf(name, "Samples\\SkinSamples\\img (%d).jpg", i);
		Mat src = imread(name, 1);
		cvtColor(src, srcHSV, CV_BGR2HSV);
		boxFilter(srcHSV, srcFilter, -1, Size(3, 3), Point(-1, -1), true, BORDER_DEFAULT);

		for (int i = 0; i < srcFilter.rows; i++)
		{
			for (int j = 0; j < srcFilter.cols; j++)
			{
				Vec3b pHSV = srcFilter.at<Vec3b>(i, j);

				dataset_file.open("skin_dataset_min.txt", ios::app);
				if ((int)pHSV[0])
					dataset_file << (int)pHSV[0] << "\t" << (int)pHSV[1] << "\t"<<(int)pHSV[2]<< "\n";
				dataset_file.close();
			}
		}
		i++;
	}
	*/

	//Get the areas of the contours in final_image
	/*ofstream contour_area_file;
	Mat dst;
	dst = Mat::zeros(final_image.size(), CV_8UC3);
	if (contours.size() == 0);
	int idx = 0; int largestComp = 0;
	double maxArea=0;
	const vector<Point>& c_temp = contours_temp[0];
	double area_temp = fabs(contourArea(Mat(c_temp)));

	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		const vector<Point>& c = contours[idx];
		double area = fabs(contourArea(Mat(c)));
		if (area > maxArea)
		{
			contour_area_file.open("contour_area_file.txt", ios::app);
			contour_area_file << area << "\n";
			contour_area_file.close();
		}
	}
	*/
	
	//read image and store it as Mat
    Mat imageHSV;
	Mat imageFilter;
	Mat temp;

	vector<vector<Point> > contours;
	vector<vector<Point> > contours_temp;
	vector<vector<Point> >  approxFace;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy_temp;


    Mat imageRGB = imread("11.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//converting from BGR -> HSV
	cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
	boxFilter(imageHSV, imageFilter, -1, Size(3, 3), Point(-1, -1), true, BORDER_DEFAULT);

	if (imageRGB.empty()){
		cout << "Error: Image cant be loaded" << endl;
		system("pause");
	}
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", imageRGB);
	Mat final_image;
	
	inRange(imageFilter, Scalar(4, 50, 142), Scalar(16, 189, 226), final_image);
	imshow("Image after Thresholding", final_image);
	temp = final_image;

	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	Mat result_temp;
	Mat template_img = imread("template.jpg", CV_LOAD_IMAGE_UNCHANGED);
	threshold(template_img, template_img, 250, 255, THRESH_BINARY);
	findContours(temp, contours_temp, hierarchy_temp, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	template_img = Mat::zeros(final_image.size(), CV_8UC3);


	ofstream contour_area_file;
	Mat dst;
	dst = Mat::zeros(final_image.size(), CV_8UC3);
	if (contours.size() == 0);
	int idx = 0; int largestComp = 0;
	double maxArea=0;
	const vector<Point>& c_temp = contours_temp[0];
	double area_temp = fabs(contourArea(Mat(c_temp)));
	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		const vector<Point>& c = contours[idx];
		double area = fabs(contourArea(Mat(c)));
		if ( area >1500)
		{
			Scalar color(0, 0, 255);
			drawContours(dst, contours, idx, color, CV_FILLED, 8, hierarchy);
		}
	}
	
	imshow("Segmented Image", dst);
		


	
	waitKey(0);
	return 0;

}
