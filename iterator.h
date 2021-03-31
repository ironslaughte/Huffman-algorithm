#pragma once
class Iterator {
public:
	virtual Node* next() = 0;
	virtual bool has_next() = 0;
};

