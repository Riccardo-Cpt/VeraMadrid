#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>

using namespace std;

int main() {
	ifstream index, inPage, inFrag;
	index.open("C:/Users/user/Documents/Cloud/Google Drive/Varie/FotoCap/index.txt", ifstream::in);
	inPage.open("C:/Users/user/Documents/Cloud/Google Drive/Varie/FotoCap/index.html", ifstream::in);
	inFrag.open("C:/Users/user/Documents/Cloud/Google Drive/Varie/FotoCap/photo.html", ifstream::in);

	ofstream outPage;
	outPage.open("C:/Users/user/Documents/Cloud/Google Drive/Varie/FotoCap/foto.html", ofstream::out);

	if(!(index.is_open() && inPage.is_open() && inFrag.is_open())) {
		return 1;
	}

	string* fileNames = new string[100];
	string* fileDescs = new string[100];
	int num = 0;
	unsigned int divIndex;

	string inLine;
	while(!index.eof()) {
		getline(index, inLine);

		divIndex = inLine.find(';');
		fileNames[num] = inLine.substr(0, divIndex);
		fileDescs[num] = inLine.substr(divIndex + 1, inLine.size() - divIndex - 1);

		num ++;
	}

	for(int i = 0; i < num; i ++) {
		cout << fileNames[i] << endl << fileDescs[i] << endl << endl;
	}

	string namesVect = "var descs = [";

	for(int i = 0; i < num; i ++) {
		namesVect = namesVect + "\"" + fileDescs[i] + "\",";
	}
	namesVect.erase(namesVect.size() - 1, 1);
	namesVect += "];";

	string inPageCont;
	while(!inPage.eof()) {
		getline(inPage, inLine);
		inPageCont += inLine;
	}

	inPageCont.replace(inPageCont.find('#'), 1, namesVect);

	string inFragCont;
	while(!inFrag.eof()) {
		getline(inFrag, inLine);
		inFragCont += inLine;
	}

	string outPagePhotos;
	for(int i = 0; i < num; i ++) {
		ostringstream conv;
		conv << i;
		outPagePhotos += "<a name=\"" + conv.str() + "\"></a>";
		divIndex = fileNames[i].find('-');
		string thisPhoto = inFragCont;
		if(divIndex == string::npos) {
			thisPhoto.replace(thisPhoto.find('@'), 1, "foto/" + fileNames[i] + ".jpg");
			outPagePhotos += thisPhoto;
		}
		else {
			thisPhoto = inFragCont;
			thisPhoto.replace(thisPhoto.find('@'), 1, "foto/" + fileNames[i].substr(0, divIndex) + ".jpg");

			outPagePhotos += thisPhoto;

			bool ex = false;
			do {
				unsigned int divIndex2 = fileNames[i].find('-', divIndex + 1);
				if(divIndex2 == string::npos) {
					divIndex2 = fileNames[i].size();
					ex = true;
				}

				thisPhoto = inFragCont;
				thisPhoto.replace(thisPhoto.find('@'), 1, "foto/" + fileNames[i].substr(divIndex + 1, divIndex2 - divIndex - 1) + ".jpg");
				outPagePhotos += thisPhoto;

				divIndex = divIndex2;
			} while(!ex);
		}
	}

	inPageCont.replace(inPageCont.find('@'), 1, outPagePhotos);

	outPage << inPageCont;

	cout << "File correttamente generato." << endl << endl;
	system("PAUSE");
}
