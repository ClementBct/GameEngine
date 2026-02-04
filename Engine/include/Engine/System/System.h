#pragma once

class System
{
public:
	System();
	~System();
	virtual void onUpdate(double i_dt_s);
	virtual void onFixedUpdate(double i_fixed_dt_s);
private:
};

