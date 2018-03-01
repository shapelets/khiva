// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>



std::vector<tsa::simplification::Point> getNextLineAndSplitIntoTokens(std::istream& str_input)
{
    std::vector<tsa::simplification::Point> result;
	std::vector<int> dates;
	std::vector<double> values;

    std::string line;
    std::stringstream linestream;
	std::string cell;
	int rown = 0;
	int celln = 0;

	struct tm mytm;
    time_t t;

	// read line
    while(std::getline(str_input, line))
    {
		linestream.str(line);
		// read cells
		while(std::getline(linestream, cell, ',')){
			tsa::simplification::Point p;

			strptime(cell.c_str(), "%Y-%m-%d", &mytm);
    		t = mktime(&mytm);
			p.first = (long) t;
			//std::cout << "Date: " << cell << " " << " Unix: " << (long)t << std::endl;
			std::getline(linestream, cell, ',');
			
			p.second = std::stof(cell);
			result.push_back(p);
			values.push_back(p.second);
			dates.push_back(t);
		}
		linestream.clear();
		rown++;
    }

	// double arrv[9376]; double arrd[9376];
	// std::copy(values.begin(), values.end(), arrv);
	// std::copy(dates.begin(), dates.end(), arrd);

	// for (int i=0; i<values.size(); i++){
	// 	std::cout << "Date: " << dates[i] << " " << " Value: " << values[i] << std::endl;
	// }

	// af::array af_values(values.size(), 1, arrv);
	// af::array  af_dates(dates.size(), 1, arrd);

	// af::saveArray("values", af_values, "WIKI_AF_values.af");
	// af::saveArray("dates", af_dates, "WIKI_AF_dates.af");

    return result;
}

void saveVectorToCSV(std::vector<tsa::simplification::Point> out, std::string filename){
	std::ofstream myfile(filename);
    int vsize = out.size();
    for(int n=0; n<vsize; n++)
    {
    	myfile << (long) out[n].first << ", " << out[n].second << std::endl;
    }
}


TEST(SimplificationTests, RamerDouglasPeuckerCPU)
{
    std::vector<tsa::simplification::Point> pointList;
	std::vector<tsa::simplification::Point> pointListOut;
	std::vector<tsa::simplification::Point> expected = {tsa::simplification::Point(0.0, 0.0), 
		tsa::simplification::Point(2.0, -0.1), tsa::simplification::Point(3.0, 5.0), 
		tsa::simplification::Point(7.0, 9.0), tsa::simplification::Point(9.0, 9.0)};
 
	pointList.push_back(tsa::simplification::Point(0.0, 0.0));
	pointList.push_back(tsa::simplification::Point(1.0, 0.1));
	pointList.push_back(tsa::simplification::Point(2.0, -0.1));
	pointList.push_back(tsa::simplification::Point(3.0, 5.0));
	pointList.push_back(tsa::simplification::Point(4.0, 6.0));
	pointList.push_back(tsa::simplification::Point(5.0, 7.0));
	pointList.push_back(tsa::simplification::Point(6.0, 8.1));
	pointList.push_back(tsa::simplification::Point(7.0, 9.0));
	pointList.push_back(tsa::simplification::Point(8.0, 9.0));
	pointList.push_back(tsa::simplification::Point(9.0, 9.0));

	// std::ifstream infile("./WIKI_data.csv");
	// pointList = getNextLineAndSplitIntoTokens(infile);
	// saveVectorToCSV(pointList, "WIKI_entry_epoch.csv");
	std::cout << "Elements in pointList " << pointList.size() << std::endl;

	pointListOut = tsa::simplification::ramerDouglasPeucker(pointList, 1.0);
	std::cout << "Elements in pointList " << pointList.size() << std::endl;
	std::cout << "Elements in pointListOut " << pointListOut.size() << std::endl;

	// saveVectorToCSV(pointListOut, "WIKI_output_epoch.csv");

	for(size_t i=0;i< pointListOut.size();i++)
	{
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
	}
}

TEST(SimplificationTests, VisvalingamCPU)
{
    std::vector<tsa::simplification::Point> pointList;
	std::vector<tsa::simplification::Point> out;
	std::vector<tsa::simplification::Point> expected = {tsa::simplification::Point(0.0, 0.0), 
		tsa::simplification::Point(2.0, -0.1), tsa::simplification::Point(5.0, 7.0), 
		tsa::simplification::Point(7.0, 9.0), tsa::simplification::Point(9.0, 9.0)};
 
	pointList.push_back(tsa::simplification::Point(0.0, 0.0));
	pointList.push_back(tsa::simplification::Point(1.0, 0.1));
	pointList.push_back(tsa::simplification::Point(2.0, -0.1));
	pointList.push_back(tsa::simplification::Point(3.0, 5.0));
	pointList.push_back(tsa::simplification::Point(4.0, 6.0));
	pointList.push_back(tsa::simplification::Point(5.0, 7.0));
	pointList.push_back(tsa::simplification::Point(6.0, 8.1));
	pointList.push_back(tsa::simplification::Point(7.0, 9.0));
	pointList.push_back(tsa::simplification::Point(8.0, 9.0));
	pointList.push_back(tsa::simplification::Point(9.0, 9.0));

	// std::ifstream infile("./WIKI_data.csv");
	// pointList = getNextLineAndSplitIntoTokens(infile);
	// saveVectorToCSV(pointList, "WIKI_entry_epoch.csv");
	std::cout << "Elements in pointList " << pointList.size() << std::endl;

	out = tsa::simplification::visvalingam_simplify(pointList, 5);
	std::cout << "Elements in pointList " << out.size() << std::endl;

	// saveVectorToCSV(pointList, "WIKI_output_epoch_vivalingam.csv");

	for(size_t i=0;i< out.size();i++){
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
	}
}