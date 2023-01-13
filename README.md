一个Windows平台上的file dialog（文件选择器）

使用Windos API commdlg.h 中的 OPENFILENAME


代码借鉴自 ： 
https://github.com/InteractiveComputerGraphics/SPlisHSPlasH

用法
```
	std::string path = fileDialog(0, ".", "All Files (*.*)\0*.*\0");
	std::cout <<"Open file: "<< path << std::endl;
```

返回的path就是选择的文件名
