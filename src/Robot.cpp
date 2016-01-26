#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	Joystick *m_leftStick;
	Joystick *m_rightStick;
	Encoder *leftDrivetrainEncoder;
	Encoder *rightDrivetrainEncoder;
	CANTalon *m_leftFront;
	CANTalon *m_rightFront;
	CANTalon *m_leftBack;
	CANTalon *m_rightBack;
	RobotDrive *m_robotDrive;
	SmartDashboard *smart;

	float ldtEncoderCount;
	float rdtEncoderCount;
	float averageEncoderCount;
	float leftMotorError;
	float rightMotorError;
	float leftStickValue;
	float rightStickValue;
	float correctedLeftMotorDemand;
	float correctedRightMotorDemand;

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		leftDrivetrainEncoder = new Encoder(0,1,false,Encoder::k4X);
		rightDrivetrainEncoder = new Encoder(2,3,false,Encoder::k4X);
		//driverstation
		m_leftStick = new Joystick(0);
		m_rightStick = new Joystick(1);
		//drivetrain
		m_leftFront = new CANTalon(0);
		m_rightFront = new CANTalon(3);
		m_leftBack = new CANTalon(1);
		m_rightBack = new CANTalon(2);
		m_robotDrive = new RobotDrive (m_leftFront, m_leftBack, m_rightFront, m_rightBack);

	}


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit()
	{
		autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void AutonomousPeriodic()
	{
		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
		} else {
			//Default Auto goes here
		}
	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		ldtEncoderCount = leftDrivetrainEncoder->Get();
		rdtEncoderCount = rightDrivetrainEncoder->Get();
		averageEncoderCount = (ldtEncoderCount+rdtEncoderCount)/2;
		leftMotorError = averageEncoderCount/ldtEncoderCount;
		rightMotorError = averageEncoderCount/rdtEncoderCount;
		leftStickValue = m_leftStick->GetY();
		rightStickValue = m_rightStick->GetY();
		correctedLeftMotorDemand = leftStickValue*leftMotorError;
		correctedRightMotorDemand = rightStickValue * rightMotorError;
		m_robotDrive->TankDrive(correctedLeftMotorDemand,correctedRightMotorDemand);
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot)
