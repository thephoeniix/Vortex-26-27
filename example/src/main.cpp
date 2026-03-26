#include "main.h"

	pros::MotorGroup left_mg({8, 10});
	pros::MotorGroup right_mg({-1, -2});
	pros::Imu imu(5);

	pros::Controller master(pros::E_CONTROLLER_MASTER);

	const int IMU_SIGN = 1; 

	struct TelemetrySample {
		double yaw = 0;
		double left_rpm = 0;
		double right_rpm = 0;
	};

	TelemetrySample latest_sample;

	void initialize() {
		pros::lcd::initialize();
		pros::lcd::set_text(0, "Robot telemetry");

		imu.reset();
		while(imu.is_calibrating()){
			pros::delay(10);
		}}

	void updateTelemetry() {
		latest_sample.yaw = IMU_SIGN * imu.get_yaw();
		latest_sample.left_rpm = left_mg.get_actual_velocity();
		latest_sample.right_rpm = right_mg.get_actual_velocity();
	}

	void printTelemetry() {
		static uint32_t last_print = 0;

		if (pros::millis() - last_print > 150) {
			last_print = pros::millis();
			updateTelemetry();

			master.print(0, 0, "Yaw:%4d      ", (int)latest_sample.yaw);
			master.print(1, 0, "L:%4d R:%4d  ", (int)latest_sample.left_rpm,
						 (int)latest_sample.right_rpm);
			pros::lcd::print(1, "Yaw: %4d", (int)latest_sample.yaw);
			pros::lcd::print(2, "L RPM: %4d", (int)latest_sample.left_rpm);
			pros::lcd::print(3, "R RPM: %4d", (int)latest_sample.right_rpm);
		}
	}

	// ================== TURN SIMPLE ==================
	void turn(double angleDeg) {
		imu.tare_yaw();
		pros::delay(100);

		const int speed = 50;

		while (true) {
			double yaw = IMU_SIGN * imu.get_yaw();

			if (std::abs(yaw) >= std::abs(angleDeg)) break;

			if (angleDeg > 0) {
				left_mg.move(speed);
				right_mg.move(speed);
			} else {
				left_mg.move(-speed);
				right_mg.move(-speed);
			}

			printTelemetry();
			pros::delay(20);
		}

		left_mg.brake();
		right_mg.brake();
	}

	// ================== DRIVE SIMPLE ==================
	void drive(double time_ms) {

    int speed = 60;

    uint32_t start_time = pros::millis();

    while ((pros::millis() - start_time) < time_ms) {

        left_mg.move(speed);
        right_mg.move(speed);

        printTelemetry();
        pros::delay(20);
    }

    left_mg.brake();
    right_mg.brake();
	}
	void autonomous() {
		turn(90); 
		drive(2000);
	}


	void opcontrol() {
		while (true) {

			int turn = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X); // girar
			int power  =  master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);  // adelante/atrás

			// Deadband
			if (std::abs(turn) < 5) turn = 0;
			if (std::abs(power)  < 5) power  = 0;

			// Mezcla
			int left_power  = power + turn;
			int right_power = power - turn;

			// Mover motores
			left_mg.move(left_power);
			right_mg.move(right_power);

			pros::delay(20);

			printTelemetry();
		}
	}
