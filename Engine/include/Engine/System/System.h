#pragma once

class System
{
public:
	System();
	~System();
private:
	virtual void onUpdate(double i_dt_s);
};

