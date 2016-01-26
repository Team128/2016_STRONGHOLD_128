#include "WPILib.h"

class Robot: public IterativeRobot
{
private:

	//default stuff
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

//initialize variables
	//driver station
	Joystick *m_leftStick;
	Joystick *m_rightStick;
	Joystick *m_gamepad;
	SmartDashboard *smart;

	//drivetrain
	CANTalon *m_leftFront;
	CANTalon *m_rightFront;
	CANTalon *m_leftBack;
	CANTalon *m_rightBack;
	RobotDrive *m_robotDrive;

	//pneumatics
		//shifters
	Solenoid *m_shifterUp;
	Solenoid *m_shifterDown;
		//shooter
	Solenoid *m_shooterExtend;
	Solenoid *m_shooterRetract;


	//timers
	Timer *lastShift;
	Timer *shooterTimer;

	//ints and floats
	int shiftValue;
	int shooterValue;
	float leftStickValue;
	float rightStickValue;
	float joystickSensitivity;


	void RobotInit()
	{
		//default stuff
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);

		//driverstation
		m_leftStick = new Joystick(0);
		m_rightStick = new Joystick(1);
		m_gamepad = new Joystick(2);

		//drivetrain
		m_leftFront = new CANTalon(0);
		m_rightFront = new CANTalon(1);
		m_leftBack = new CANTalon(2);
		m_rightBack = new CANTalon(3);
		m_shifterUp = new Solenoid(6);
		m_shifterDown = new Solenoid(7);
		m_robotDrive = new RobotDrive (m_leftFront, m_leftBack, m_rightFront, m_rightBack);
		m_robotDrive->SetSafetyEnabled(false);

		//shooter
		m_shooterExtend = new Solenoid(8);
		m_shooterRetract = new Solenoid(9);

		//timers
		lastShift = new Timer();
		shooterTimer = new Timer();

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
		shiftValue = 0;
		lastShift->Start();

	}

	void TeleopPeriodic()
	{
		TeleopDrive();
		Shift();
		Shooter();

	}

	void TestPeriodic()
	{
		lw->Run();
		TeleopDrive();
		Shift();
		Shooter();
	}

	void TeleopDrive()
	{
		leftStickValue = m_leftStick->GetY();
		rightStickValue = m_rightStick->GetY();
		m_robotDrive->TankDrive(leftStickValue, rightStickValue);

	}

	void Shift()
	{
		if(m_leftStick->GetTrigger()== 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 1 && lastShift->Get() > 0.3)
		{
			m_shifterUp->Set(true);
			m_shifterDown->Set(false);
			shiftValue = 1;
			lastShift->Reset();
		}
		else if(m_leftStick->GetTrigger() == 1 && m_rightStick->GetTrigger() == 1 && shiftValue == 0 && lastShift->Get() > 0.3)
		{
			m_shifterUp->Set(false);
			m_shifterDown->Set(true);
			shiftValue = 0;
			lastShift->Reset();
		}
	}

	void Shooter()
	{
		if(m_gamepad->GetRawButton(1) == 1 && shooterTimer->Get() > 0.3 && shooterValue == 0)
		{
			m_shooterExtend->Set(true);
			m_shooterRetract->Set(false);
			shooterTimer->Reset();
			shooterValue = 1;
		}
		else if(shooterTimer->Get() > 0.3 && shooterValue == 1)
		{
			m_shooterExtend->Set(false);
			m_shooterRetract->Set(true);
			shooterTimer->Reset();
			shooterValue = 0;
		}
	}
};

START_ROBOT_CLASS(Robot)
