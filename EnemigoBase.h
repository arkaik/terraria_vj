#pragma once
class EnemigoBase {
public:
	EnemigoBase(int vida);
	int getVida();
	void setVida(int vida);
	bool estaMuerto();
	void disminuirVida(int dis);
protected:
	int vida;
};
