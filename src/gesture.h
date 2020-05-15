
#ifndef _GESTURE_H
#define _GESTURE_H

class Gesture
{
public:
	Gesture();
	~Gesture();
	void Open(int x, int y);
	void Drag(int x, int y);
	void Close(void);
	bool IsOpen() { return fOpen; }
	
private:
	void UpdateRect(int x, int y);
	void ProcessString(const char *str);
	
	BString *fString;
	BRect fRect;
	bool fOpen;
};



#endif
