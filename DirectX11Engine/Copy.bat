xcopy /s /y /exclude:IgnoreCopy.txt ".\Project\Engine\*.h" ".\External\Include\Engine"
xcopy /s /y /exclude:IgnoreCopy.txt ".\Project\Engine\*.inl" ".\External\Include\Engine"
xcopy /s /y /exclude:IgnoreCopy.txt ".\Project\Engine\*.fx" ".\OutputFile\content\shader"