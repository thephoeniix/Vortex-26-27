#include "main.h"

pros::MotorGroup left_mg({8, 10});
pros::MotorGroup right_mg({-1, -2});
pros::Imu imu(5);
pros::Controller master(pros::E_CONTROLLER_MASTER);

const int IMU_SIGN = -1;
const int SAMPLE_DELAY_MS = 10;
const int MAX_TELEMETRY_SAMPLES = 1200;
const int DRIVE_SPEED = 60;
const int TURN_SPEED = 50;

struct TelemetrySample {
	uint32_t time_ms = 0;
	double yaw = 0;
	double left_rpm = 0;
	double right_rpm = 0;
};

TelemetrySample latest_sample;
TelemetrySample telemetry_log[MAX_TELEMETRY_SAMPLES];
int telemetry_count = 0;

void initialize() {
	pros::lcd::initialize();
	pros::lcd::print(0, "A: turn 90  B: drive");
	pros::lcd::print(1, "Esperando prueba");

	imu.reset();
	while (imu.is_calibrating()) {
		pros::delay(10);
	}
}

void stopDrive() {
	left_mg.brake();
	right_mg.brake();
}

void resetTelemetryLog() {
	telemetry_count = 0;
}

void updateTelemetrySample(uint32_t start_time_ms) {
	latest_sample.time_ms = pros::millis() - start_time_ms;
	latest_sample.yaw = IMU_SIGN * imu.get_yaw();
	latest_sample.left_rpm = left_mg.get_actual_velocity();
	latest_sample.right_rpm = right_mg.get_actual_velocity();
}

void saveTelemetrySample(uint32_t start_time_ms) {
	updateTelemetrySample(start_time_ms);

	if (telemetry_count < MAX_TELEMETRY_SAMPLES) {
		telemetry_log[telemetry_count] = latest_sample;
		telemetry_count++;
	}
}

void printLiveTelemetry(const char* test_name) {
	static uint32_t last_print = 0;

	if (pros::millis() - last_print < 100) {
		return;
	}

	last_print = pros::millis();
	master.print(0, 0, "%s Y:%4d", test_name, (int)latest_sample.yaw);
	master.print(1, 0, "L:%4d R:%4d", (int)latest_sample.left_rpm,
				 (int)latest_sample.right_rpm);
	pros::lcd::print(1, "%s", test_name);
	pros::lcd::print(2, "t:%4lu y:%4d", (unsigned long)latest_sample.time_ms,
					 (int)latest_sample.yaw);
	pros::lcd::print(3, "L:%4d R:%4d", (int)latest_sample.left_rpm,
					 (int)latest_sample.right_rpm);
	pros::lcd::print(4, "samples:%4d", telemetry_count);
}

void dumpTelemetryCsv(const char* test_name) {
	printf("\n--- %s CSV START ---\n", test_name);
	printf("index,time_ms,yaw,left_rpm,right_rpm\n");

	for (int i = 0; i < telemetry_count; i++) {
		const TelemetrySample& sample = telemetry_log[i];
		printf("%d,%lu,%.2f,%.2f,%.2f\n", i, (unsigned long)sample.time_ms,
			   sample.yaw, sample.left_rpm, sample.right_rpm);
	}

	printf("--- %s CSV END ---\n", test_name);
	fflush(stdout);
}

void runDriveTest(uint32_t drive_time_ms) {
	const uint32_t start_time_ms = pros::millis();

	imu.tare_yaw();
	resetTelemetryLog();

	while ((pros::millis() - start_time_ms) < drive_time_ms) {
		left_mg.move(DRIVE_SPEED);
		right_mg.move(DRIVE_SPEED);
		saveTelemetrySample(start_time_ms);
		printLiveTelemetry("DRIVE");
		pros::delay(SAMPLE_DELAY_MS);
	}

	stopDrive();
	saveTelemetrySample(start_time_ms);
	printLiveTelemetry("DRIVE");
	dumpTelemetryCsv("DRIVE");
}

void runTurnTest(double angle_deg) {
	const uint32_t start_time_ms = pros::millis();

	imu.tare_yaw();
	resetTelemetryLog();

	while (true) {
		double yaw = IMU_SIGN * imu.get_yaw();

		if (std::abs(yaw) >= std::abs(angle_deg)) {
			break;
		}

		if (angle_deg > 0) {
			left_mg.move(TURN_SPEED);
			right_mg.move(-TURN_SPEED);
		} else {
			left_mg.move(-TURN_SPEED);
			right_mg.move(TURN_SPEED);
		}

		saveTelemetrySample(start_time_ms);
		printLiveTelemetry("TURN");
		pros::delay(SAMPLE_DELAY_MS);
	}

	stopDrive();
	saveTelemetrySample(start_time_ms);
	printLiveTelemetry("TURN");
	printf("[turn] target=%.2f final=%.2f error=%.2f\n", angle_deg,
		   latest_sample.yaw, angle_deg - latest_sample.yaw);
	fflush(stdout);
	dumpTelemetryCsv("TURN");
}

void autonomous() {
	runTurnTest(90);
}

void opcontrol() {
	bool last_a_press = false;
	bool last_b_press = false;

	while (true) {
		bool a_press = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
		bool b_press = master.get_digital(pros::E_CONTROLLER_DIGITAL_B);

		if (a_press && !last_a_press) {
			runTurnTest(90);
		}

		if (b_press && !last_b_press) {
			runDriveTest(3000);
		}

		last_a_press = a_press;
		last_b_press = b_press;
		pros::delay(20);
	}
}
