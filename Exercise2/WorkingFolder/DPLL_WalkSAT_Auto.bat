@echo off
setlocal enabledelayedexpansion
goto :main

:main
setlocal

	set /a M = 5
	set /a counter = 1
	set /a limit = 17
	set solved1 = 0
	set solved2 = 0
	
	:loop
	if !counter! lss !limit! (
		
		set /a counter2 = 1
		set /a limit2 = 11
		:loop2
		if !counter2! lss !limit2! (
			echo !M! >> WalkSatDpllDiagram2RawData.txt
			AIAsk2.exe walksat 2Input_!counter!_!counter2!.txt WalkSatOutput_!counter!_!counter2!.txt >> WalkSatDpllDiagram2RawData.txt
			FOR /F "USEBACKQ" %%F IN (`BCSP_Validate.exe 2Input_!counter!_!counter2!.txt WalkSatOutput_!counter!_!counter2!.txt`) DO (
				SET solved1=%%F
			)
			echo|set /p=!solved1!
			AIAsk2.exe dpll 2Input_!counter!_!counter2!.txt DpllOutput_!counter!_!counter2!.txt >> WalkSatDpllDiagram2RawData.txt
			FOR /F "USEBACKQ" %%F IN (`BCSP_Validate.exe 2Input_!counter!_!counter2!.txt DpllOutput_!counter!_!counter2!.txt`) DO (
				SET solved2=%%F
			)
			echo !solved2!
			
			if !solved1! == 1 (
				if !solved2! == 1 (
					echo !M! 1 1 >> WalkSatDpllDiagram1RawData.txt
				) else (
					echo !M! 1 0 >> WalkSatDpllDiagram1RawData.txt
				)
				
			) else (
				if !solved2! == 1 (
					echo !M! 0 1 >> WalkSatDpllDiagram1RawData.txt
				) else (
					echo !M! 0 0 >> WalkSatDpllDiagram1RawData.txt
				)
			)
			
			set /a counter2 = !counter2! + 1
			goto :loop2
		)
		
		set /a temp = !M!/2
		set /a M = !M! + !temp!
		set /a counter = !counter! + 1
		goto :loop
	)
	
	BCSP_GenDiagramData.exe 1 WalkSatDpllDiagram1RawData.txt WalkSatDpllDiagram1Data.txt
	echo Diagram 1 data done
	BCSP_GenDiagramData.exe 2 WalkSatDpllDiagram2RawData.txt WalkSatDpllDiagram2Data.txt
	echo Diagram 2 data done

endlocal
goto :eof