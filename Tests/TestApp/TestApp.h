#pragma once

class TestApp
{
public:
	void run();

private:
	void printHeader(const char* title) const;
	void printPass(const char* label, bool condition) const;
	void pause() const;

	void runContainerVectorTest();
	void runSLinkedListTest();
	void runPoint2DTest();
	void runPoint3DTest();
	void runVector2DTest();
	void runVector3DTest();
	void runConvexHull2DTest();
	void runSmartPointerTest();
	void runAllTests();
};
