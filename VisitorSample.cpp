#include <iostream>
#include <string>

using namespace std;

class Environment;
class Forest;
class Coastal;
class Desert;

// Basic Visitor class
class Visitor{
public:
	virtual void InteractForest(Forest *F) = 0;
	virtual void InteractCoastal(Coastal *C) = 0;
	virtual void InteractDesert(Desert* D) = 0;
};

class Environment{
protected:
	string code_name;
	float area;
public:
	Environment(string name = "Default name", float a = 100) : code_name(name), area(a) {}
	string getName() {
		return code_name;
	}
	virtual void InteractVisitor(Visitor *v) = 0;
};

class Forest : public Environment {
protected:
	float tree_density;
public:
	Forest(string name = "Default Forest name", float a = 100, float tD = 0.8) : Environment(name, a), tree_density(tD){}
	
	void InteractVisitor(Visitor *v){
		v->InteractForest(this);
	}
	
	float getTreeDensity(){
		return tree_density;
	}
};

class Coastal : public Environment {
protected:
	float average_sea_level;
public:
	Coastal(string name = "Default Coastal name", float a = 100, float aSL = 1.5) : Environment(name, a), average_sea_level(aSL) {}
	
	void InteractVisitor(Visitor *v){
		v->InteractCoastal(this);
	}
	
	float getSeaLevel(){
		return average_sea_level;
	}
};

class Desert : public Environment {
protected:
	float average_temp;
public:
	Desert(string name = "Default Desert name", float a = 100, float aT = 80) : Environment(name, a), average_temp(aT) {}

	void InteractVisitor(Visitor *v){
		v->InteractDesert(this);
	}
	
	float getDesertTemp(){
		return average_temp;
	}
};

class GetInfoVisitor : public Visitor{
public:
	void InteractForest(Forest *F){
		cout << F->getName() << endl;
		cout << "Current tree density: " << F->getTreeDensity() << endl;
	}
	void InteractCoastal(Coastal *C){
		cout << C->getName() << endl;
		cout << "Current average sea level: " << C->getSeaLevel() << endl;
	}
	void InteractDesert(Desert* D){
		cout << D->getName() << endl;
		cout << "Current average temperature: " << D->getDesertTemp() << endl;
	}
};

class CheckStateVisitor : public Visitor{
private:
	int warnings;
public:
	CheckStateVisitor() : warnings(0) {}
	void InteractForest(Forest *F){
		if (F->getTreeDensity() > 1){
			cout << "Concerning tree density level at: " << F->getName() << endl;
			warnings++;
		}
	}
	void InteractCoastal(Coastal *C){
		if (C->getSeaLevel() > 4){
			cout << "Concerning water level at: " << C->getName() << endl;
			warnings++;
		}
	}
	void InteractDesert(Desert* D){
		if (D->getDesertTemp() > 120){
			cout << "Concerning tempature level at: " << D->getName() << endl;
			warnings++;
		}
	}
	
	int Results(){
		return warnings;
	}
};

//
//void AnalyzeData(Environment *list[], int n){
//	cout << "Getting data from sources..." << endl;
//	for (int i = 0; i < n; i++)
//		if (dynamic_cast<Forest*>(list[i])){
//			Forest *F = list[i];
//			F->getTreeDensity();
//			...
//		}
//		if (dynamic_cast<Coastal*>(list[i]))
//		...
//}

void AnalyzeData(Environment *list[], int n){
	GetInfoVisitor *getInfo = new GetInfoVisitor;
	CheckStateVisitor *check = new CheckStateVisitor;

	cout << "Getting data from sources..." << endl;
	for (int i = 0; i < n; i++)
		list[i]->InteractVisitor(getInfo);
	
	cout << "Scanning for warnings..." << endl;
	for (int i = 0; i < n; i++)
		list[i]->InteractVisitor(check);
	
	cout << check->Results() << " warnings." << endl;
	
	delete getInfo;
	delete check;
}
int main(){
	Forest *sampleForest = new Forest("Amazon", 100, 1.8);
	Coastal *sampleCoastal = new Coastal("Phu_Quoc", 200, 1.6);
	Desert *sampleDesert = new Desert("Sahara", 300, 180);
	
	Environment *list[3] = {sampleForest, sampleCoastal, sampleDesert};
	
	AnalyzeData(list, 3);
	
	delete sampleForest;
	delete sampleCoastal;
	delete sampleDesert;
	
	return 0;	
}


