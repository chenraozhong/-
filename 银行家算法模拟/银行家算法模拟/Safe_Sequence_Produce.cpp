#include "stdafx.h"
#include"Safe_Sequence_Produce.h"
#include<fstream>
#include<string>
#include<sstream>
#include<map>
#include"gobal.h"
using namespace std;
#ifndef _SAFE_SEQUENCE_PRODUCE_CPP
#define _SAFE_SEQUENCE_PRODUCE_CPP

int _SystemTime = 0;
int _ThreholdValue = 30;

void Eraser(vector<int> &sequence, int value) {
	vector<int>::iterator myitem = sequence.begin();
	for (; myitem != sequence.end(); myitem++) {
		if (*myitem == value) break;
	}
	if (myitem == sequence.end()) {
		cerr << "�������޴���ֵ������";
		exit(1);
	}
	else sequence.erase(myitem);
}

void Push_Back(vector<int> &sequence, int value) {
	vector<int>::iterator myitem = sequence.begin();
	for (; myitem != sequence.end(); myitem++) {
		if (*myitem == value) break;
	}
	if (myitem != sequence.end()) {
		cerr << "�����Ѵ�����ֵ������";
		exit(1);
	}
	else sequence.push_back(value);
}

int StrToNum(string str) {
	stringstream ss(str);
	int myvalue = 0;
	ss >> myvalue;
	return myvalue;
}

/*
���ַ���strת�������ֲ��洢��value��
*/
void StrToVector(string str, vector<int> &value) {
	char myletter = ' ';
	int myvalue = 0;
	string mydigal = "";
	for (int i = 0; i < str.size(); i++) {
		myletter = str[i];
		if (myletter == ' ') {
			myvalue = StrToNum(mydigal);
			value.push_back(myvalue);
			mydigal = "";
			continue;
		}
		else {
			mydigal += myletter;
		}
	}
	if (!mydigal.empty()) {
		myvalue = StrToNum(mydigal);
		value.push_back(myvalue);
	}
}

/*
����file�ĵ��ж�ȡ����Ϣ�洢��value��
*/
void FileToVector(string file, vector<vector<int> > &value) {
	ifstream in;
	in.open(file);
	if (!in) {
		cerr << file << "�ļ���ʧ��";
	}
	string mystr;
	getline(in, mystr);
	while (!in.eof()) {
		vector<int> myvalue;
		StrToVector(mystr, myvalue);
		value.push_back(myvalue);
		getline(in, mystr);
	}
	in.close();
}

SqeCls::SqeCls() {
	m_SafeAndScore.open("SafeAndScore.txt");
}

SqeCls::~SqeCls() {
	m_SafeAndScore.close();
}

void SqeCls::SqeCls_Sourseinit() {//��ϵͳ��Դ���и���
	ifstream in;
	string myfile = "Available.txt";
	in.open(myfile);
	if (!in) {
		cerr << myfile << "�ļ���ʧ��";
	}
	string mystr = "";
	getline(in, mystr);
	StrToVector(mystr, m_Source);
	in.close();
}

void SqeCls::SqeCls_Remaininit() {
	for (int i = 0; i < m_Source.size(); i++) {
		int sum = 0;
		for (int j = 0; j < m_Allocation.size(); j++) {
			sum += m_Allocation[j][i];
		}
		m_Remain.push_back(m_Source[i] - sum);
	}
}

void SqeCls::SqeCls_Allocationinit() {
	FileToVector("Allocation.txt", m_Allocation);//�����ļ��ж�ȡ���ַ���ת����vector����
}

void SqeCls::SqeCls_Durationinit() {
	FileToVector("Duration.txt", m_Duration);
}

void SqeCls::SqeCls_MAXRequestinit() {
	FileToVector("Max.txt", m_MAXRequest);
}

void SqeCls::SqeCls_Requestinit() {
	for (int i = 0; i < m_Allocation.size(); i++) {
		vector<int> value;
		for (int j = 0; j < m_Source.size(); j++) {
			value.push_back(m_MAXRequest[i][j] - m_Allocation[i][j]);
		}
		m_Request.push_back(value);
	}
}

void SqeCls::SqeCls_Releaseinit() {
	for (int i = 0; i < m_Source.size(); i++) {
		map<int, int> myvalue;
		m_Release.push_back(myvalue);
	}
}

void SqeCls::SqeCls_Messageinit() {
	SqeCls_Sourseinit();//��ʼ��ϵͳ��Դ
	SqeCls_Allocationinit();//��ʼ���ѷ�����Դ
	SqeCls_Durationinit();//��ʼ���ͻ�ռ����Դʱ��
	SqeCls_Remaininit();//��ʼ��ϵͳʣ����Դ
	SqeCls_MAXRequestinit();//��ʼ���ͻ����������
	SqeCls_Requestinit();//��ʼ���ͻ�������Դ
	SqeCls_Releaseinit();//��ʼ������Դ�ͷ���Ϣ
	m_clientnum = m_Allocation.size();
	m_sourcenum = m_Source.size();
}

/*
����ϵͳʣ����Դ��Ϣ������currtime֮ǰ����Դ���ͷŵ���Դȫ���ͷŵ�
*/
void SqeCls::SqeCls_UpdateRemain(vector<int> remain,vector<map<int,int> > release,int currtime) {
	for (int i = 0; i < remain.size(); i++) {
		map<int, int>::iterator myitem = release[i].find(currtime);
		if (myitem == release[i].end()) continue;//��ʾ��currtime,��Դi���ͷ�
		else {
			remain[i] += release[i][currtime];
			release[i].erase(currtime);
		}
	}
}

int SqeCls::SqeCls_CacluApplyTime(int num,int currtime,vector<int> Remain,vector<map<int,int> > release) {
	vector<int> myremain = Remain;
	int mycount = 0;//��¼�Ѿ����ɵ���Դ������
	vector<int> myAllocation;
	for (int i = 0; i < m_Source.size(); i++)
		myAllocation.push_back(0);
	while (mycount < m_Source.size()) {
		int mynum;
		int i = 0;
		for (; i < myAllocation.size(); i++) {
			if (myAllocation[i] != 0) continue;
			else if (myremain[i] >= m_Request[num][i]) {
				myAllocation[i] = 1;
				mycount++;
			}
		}//end of for
		currtime++;
		SqeCls_UpdateRemain(myremain,release, currtime);//����ϵͳʣ����Դ
	}//end of while
	return currtime;
}

/*
������Դ��δ���ͷ���Ϣ
*/
void SqeCls::SqeCls_UpdateRelease(vector<map<int, int> > release, int num,int currtime) {
	int myrelease = 0;
	for (int i = 0; i < m_Source.size(); i++) {
		myrelease = currtime + m_Duration[num][i];
		map<int, int>::iterator myitem = release[i].find(myrelease);
		if (myitem != release[i].end()) release[i][myrelease] += m_MAXRequest[num][i];
		else release[i][myrelease] = m_MAXRequest[num][i];
	}
}

void SqeCls::SqeCls_UpdateMessage(vector<int> remain, vector<map<int, int> > release, int &currtime, int applytime, int num) {
	_SystemTime += (applytime - currtime);//����ȫ��ϵͳʱ��
	while (currtime <= applytime) {
		currtime ++;
		SqeCls_UpdateRemain(remain, release, currtime);
		SqeCls_UpdateRelease(release, num, currtime);
	}
}

/*
�б�ͻ�num�ܲ��ܲ��밲ȫ�����У����򷵻�true,���򷵻�false
*/
bool SqeCls::SqeCls_Client_Is_Safe(int num, vector<map<int, int> > release, vector<int> remain) {
	vector<int> myremain = remain;
	for (int i = 0; i < remain.size(); i++) {
		if (release[i].empty()) continue;
		map<int, int>::iterator myitem = release[i].begin();
		remain[i] += myitem->second;
	}//end of for
	for (int i = 0; i < m_Request[num].size(); i++) {
		if (m_Request[num][i] > myremain[i]) return false;
	}//end of for
	return true;
}

int SqeCls::SqeCls_FindClient(vector<int> safe, vector<int> pendsearch, vector<map<int, int> > release, vector<int> remain) {
	for (int i = 0; i < pendsearch.size(); i++) {
		if (SqeCls_Client_Is_Safe(pendsearch[i], release, remain))  return pendsearch[i];//����ͻ�pendsearch[i]�ܲ��밲ȫ�����У��򷵻�pendserach[i]
	}
	return -1;
}

/*
����ȫ����Դ�ͷ�ʱ��
*/
int SqeCls::SqeCls_CacluTotalReleaseTime(int currtime,vector<map<int,int> > release ) {
	int mymaxtime = 0;
	for (int i = 0; i < release.size(); i++) {
		map<int, int>::iterator myitem = release[i].begin();
		for (; myitem != release[i].end(); myitem++) {
			if (mymaxtime < myitem->first) mymaxtime = myitem->first;
		}
	}//end of for
	return currtime + mymaxtime;
}

/*
������Դ������
*/
double SqeCls::SqeCls_CacluSourceRation(vector<int> remain) {
	double myratio = 0.0;
	for (int i = 0; i < remain.size(); i++) {
		myratio += (double(remain[i]) /double( m_Source[i]));
	}
	return myratio;
}

/*
��ȫ����Դ����ʱ�䡢ȫ����Դ�ͷ�ʱ�䡢��Դ�����ʽ��м�Ȩ���㣬�õ��÷�
*/
double SqeCls::SqeCls_Cacluate(int totalApplytime, int totalReleaseTime, double sourceration) {
	double myscore = double(_SystemTime)/double(totalApplytime)*0.6+double(_SystemTime)/double(totalReleaseTime)*0.4+sourceration;//Ȩֵ���д���ȶ
	return myscore;
}

/*
�÷ּ���ģ�飬����÷֣�������ȫ���к͵÷������SafeAndScore.txt��
*/
void SqeCls::SqeCls_CacluScore(vector<int> safe,int currtime,vector<map<int,int> > release,vector<int> remain) {
	int mytotalApplyTime = currtime;
	int mytotalReleaseTime = SqeCls_CacluTotalReleaseTime(currtime, release);
	double mySourceRation = SqeCls_CacluSourceRation(remain);
	double myScore = SqeCls_Cacluate(mytotalApplyTime, mytotalReleaseTime, mySourceRation);
	for (int i = 0; i < safe.size(); i++)
		m_SafeAndScore << safe[i] << " ";
	m_SafeAndScore << endl;
	m_SafeAndScore << myScore;
	m_SafeAndScore << endl;
}

void SqeCls::SqeCls_Allocation(int num, int currtime, vector<map<int, int> > release, vector<int> remain, vector<int> safe, vector<int> pendsearch) {
	if (_SystemTime <= _ThreholdValue) {
		int myclientnum = 0;
		Push_Back(safe, num);
		//Eraser(pendsearch, num);
		while (myclientnum != -1) {
			myclientnum = SqeCls_FindClient(safe, pendsearch, release, remain);
			if (myclientnum == -1) {//��ʾ���Ҳ����ɲ������е��û�
				if (safe.size() == m_clientnum)//��ʾ�������ǰ�ȫ����
					SqeCls_CacluScore(safe,currtime,release,remain);//end of if
				else {
					cout << "�����в��ǰ�ȫ����" << endl;
				}
			}
			else {
				Eraser(pendsearch, myclientnum);
				int myapplytime = SqeCls_CacluApplyTime(num, currtime, remain, release);
				int mycurrtime = currtime;
				vector<int> myremain = remain;
				vector<map<int, int> > myrelease = release;
				vector<int> mysafe = safe;
				vector<int> mypendsearch = pendsearch;
				SqeCls_UpdateMessage(myremain, myrelease, mycurrtime, myapplytime, num);
				SqeCls_Allocation(myclientnum, currtime, myrelease, myremain, mysafe, mypendsearch);
			}
		}//end of while
	}//end of if 
}

void SqeCls::SqeCls_Run() {
	SqeCls_Messageinit();
	int mycurrtime = 0;
	vector<int> myremain = m_Remain;
	vector<map<int, int> > myrelease=m_Release;
	vector<int> mysafe;
	vector<int> mypendsearch;
	for (int i = 0; i < m_clientnum; i++) mypendsearch.push_back(i);
	int num=SqeCls_FindClient(mysafe, mypendsearch, m_Release, m_Remain);
	if (num == -1) {
		cerr << "������ɵ���Ϣ�ް�ȫ���У�����������";
		exit(1);
	}
	//mysafe.push_back(num);
	Eraser(mypendsearch, num);
	int myapplytime = SqeCls_CacluApplyTime(num, mycurrtime, myremain, myrelease);
	SqeCls_UpdateMessage(myremain, myrelease, mycurrtime, myapplytime, num);
	SqeCls_Allocation(num, mycurrtime, myrelease, myremain, mysafe, mypendsearch);
}

#endif // !_SAFE_SEQUENCE_PRODUCE_CPP
