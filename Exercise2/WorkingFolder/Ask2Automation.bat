@echo off
setlocal enabledelayedexpansion
goto :main

:main
setlocal

	set /a M = 5
	set /a counter = 1
	set /a limit = 17
	set /a temp = 0
	set /a solvedN = 0
	
	:loop
	if !counter! lss !limit! (
		BCSP_Generate.exe 2Input_!counter! 1 10 !M!
		
		set /a counter2 = 1
		set /a limit2 = 11
		echo !M!
		:loop2
		if !counter2! lss !limit2! (
			AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt > nul
			FOR /F "USEBACKQ" %%F IN (`BCSP_Validate.exe 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt`) DO (
				SET solved=%%F
			)
			
			if !solved! == 1 (
				set /a solvedN = !solvedN! + 1
				echo !M! 1 >> _Diagram1RawData.txt
				echo !M! >> _Diagram2RawData.txt
				AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt >> _Diagram2RawData.txt
				AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt >> _Diagram2RawData.txt
				AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt >> _Diagram2RawData.txt
				AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt >> _Diagram2RawData.txt
				AIAsk2.exe hill 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!.txt >> _Diagram2RawData.txt
				AIAsk2.exe depth 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!_D.txt >> _Diagram2RawData.txt
				AIAsk2.exe walksat 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!_W.txt >> _Diagram2RawData.txt
				AIAsk2.exe dpll 2Input_!counter!_!counter2!.txt 2Output_!counter!_!counter2!_DPLL.txt >> _Diagram2RawData.txt
			) else (
				echo !M! 0 >> _Diagram1RawData.txt
			)
			
			set /a counter2 = !counter2! + 1
			goto :loop2
		)
		
		set /a temp = !M!/3 * 2
		set /a M = !M! + !temp!
		set /a counter = !counter! + 1
		goto :loop
	)
	
	BCSP_GenDiagramData.exe 1 _Diagram1RawData.txt _Diagram1Data.txt
	echo Diagram 1 data done
	BCSP_GenDiagramData.exe 2 _Diagram2RawData.txt _Diagram2Data.txt _Diagram3Data.txt
	echo Diagram 2 data done

endlocal
goto :eof