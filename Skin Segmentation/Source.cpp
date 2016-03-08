#include <opencv2\opencv.hpp>
#include <fstream>

using namespace cv;
using namespace std;

/*--------------- SKIN SEGMENTATION ---------------*/
int main() {
	
	// read image and store it as Mat
    Mat imageHSV;
	Mat imageFilter;
	Mat temp;

	vector<vector<Point> > contours;
	vector<vector<Point> > contours_temp;
	vector<vector<Point> >  approxFace;
	vector<Vec4i> hierarchy;
	vector<Vec4i> hierarchy_temp;


    Mat imageRGB = imread("images\8.jpg", CV_LOAD_IMAGE_UNCHANGED);
	
	// convert from BGR -> HSV
	cvtColor(imageRGB, imageHSV, COLOR_BGR2HSV);
	boxFilter(imageHSV, imageFilter, -1, Size(3, 3), Point(-1, -1), true, BORDER_DEFAULT);

	// handle error if no image is found
	if (imageRGB.empty()){
		cout << "Error: Image cant be loaded" << endl;
		system("pause");
	}

	// show image in window
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", imageRGB);
	Mat final_image;
	
	// filter image within this range of color
	inRange(imageFilter, Scalar(4, 50, 142), Scalar(16, 189, 226), final_image);
	imshow("Image after Thresholding", final_image);
	temp = final_image;

	// contour temp image
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	Mat result_temp;
	Mat template_img = imread("images\template.jpg", CV_LOAD_IMAGE_UNCHANGED);

	// binarize the image
	threshold(template_img, template_img, 250, 255, THRESH_BINARY);
	findContours(temp, contours_temp, hierarchy_temp, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	template_img = Mat::zeros(final_image.size(), CV_8UC3);


	ofstream contour_area_file;
	Mat dst;
	dst = Mat::zeros(final_image.size(), CV_8UC3);
	if (contours.size() == 0);
	int idx = 0; int largestComp = 0;

	// segment faces with a max area 
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
