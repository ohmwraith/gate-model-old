#include "Gate.cpp"
using namespace System::Windows::Forms;
#pragma once
ref class Car
{
protected:
	//���� (����� �������� �� ��������)
	Gate^ gate;
	int number, color_id, speed, direction, status;
private:

public:
	//�������� ��� �������
	delegate void CarEventHandler(int number);
	delegate void CarCreatedHandler(int number, int color, int spd, int dir);
	delegate void CarChangedHandler(int number, int color, int spd, int dir);
	delegate void CarStatusHandler(int number, int status);
	//������� �������.
	static event CarCreatedHandler^ CREATED;
	// ������� ��������� ���������� ������. �� ���� �������� ������ ���������.
	static event CarChangedHandler^ CHANGED;
	// ������� ����������� ������. ����������, ����� ������ �������� ������� ���������.
	static event CarStatusHandler^ KILL;
	static event CarEventHandler^ goToGateEvent;
	static event CarEventHandler^ goThrowGateEvent;
	static event CarEventHandler^ goToParkEvent;


	Car(int n, int color, int spd, int dir) {
		//���������� ����� ������
		number = n;
		//������ ������ ������������� ���� ����
		color_id = color;
		//�������� ������ ������ ����� ����������
		speed = spd;
		//����������� �������� ������ (0 - �� ��������, 1 - � ��������)
		direction = dir;
		//��������� ������ (0 - �� ������(������), 1 - � ���������, 2 - ����� ���������, 3 - �������� �� ��������)
		status = 0;
		CREATED(number, color_id, speed, direction);
		gate->OPENED += gcnew Gate::GateEventHandler(this, &Car::go_throw_gate);
		gate->CLOSED += gcnew Gate::GateEventHandler(this, &Car::go_to_gate);
	}
	property int p_number {
		int get() { return number; };
		//void set(int new_number) { CHANGED(number); number = new_number; };
	}
	property int p_color {
		int get() { return color_id; };
		void set(int new_color) { CHANGED(number, color_id, speed, direction); color_id = new_color; };
	}
	property int p_speed {
		int get() { return speed; };
		void set(int new_speed) { CHANGED(number, color_id, speed, direction); color_id = new_speed; };
	}
	property int p_direction {
		int get() { return direction; };
		void set(int new_direction) { CHANGED(number, color_id, speed, direction); color_id = new_direction; };
	}
	//���������� ������� �� ������ ������ ����� �������� ������
	void go_throw_gate() {
		goThrowGateEvent(number);
	}
	//���������� ������� ��������� � ������� � ������������ � ���
	void go_to_gate() {
		goToGateEvent(number);
	}
	void go_to_park() {
		goToParkEvent(number);
	}
	//���������� ������� �� ����������� ����������
	void destroy() {
		KILL(number, -1);
	}
	void incoming_car_request() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Create");
			sa->WriteLine("Direction=up");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	void leaving_car_request() {
		try{
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Create");
			sa->WriteLine("Direction=down");
			sa->WriteLine("Event=Forward");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	void send_forward() {
		try {
			System::IO::StreamWriter^ sa = System::IO::File::AppendText("./Interface.txt");
			sa->WriteLine("Car:");
			sa->WriteLine("Event=Forward");
			sa->WriteLine("Direction=up");
			sa->WriteLine("Number=" + number);
			sa->Close();
		}
		catch (System::IO::IOException^ e) {
			MessageBox::Show("�������� ������ ������ ����������, ��� �� ��������� �� ���������������� ���������, ������������� ������ �������� ������������", "��������", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
};

