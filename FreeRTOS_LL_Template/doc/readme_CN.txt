/**
  @page Template Description of the Templates project
  
  @verbatim
  ******************** (C) COPYRIGHT 2016 STMicroelectronics *******************
  * @file    Project/STM32F4xx_StdPeriph_Templates/readme.txt 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Description of the TEMPLATE example
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the Licens
  *   
  ******************************************************************************
  @endverbatim

@par 示例说明

该示例作为模板工程，可作为参考，用于使用 STM32F4xx 标准外设库
为下列器件构建新的固件应用：
STM32F405xx/407xx、STM32F415xx/417xx、STM32F427xx/437xx、
STM32F429xx/439xx、STM32F401xx/410xx/411xE、STM32F412xx、STM32F446xx、STM32F469xx/479xx
或 STM32F413_423xx 设备。

@par 目录内容

  - Template/system_stm32f4xx.c   STM32F4xx 系统时钟配置文件
  - Template/stm32f4xx_conf.h     库配置文件
  - Template/stm32f4xx_it.c       中断处理程序
  - Template/stm32f4xx_it.h       中断处理程序头文件
  - Template/main.c               主程序
  - Template/main.h               主程序头文件

@par 硬件与软件环境

  - 该示例可在 STM32F405xx/407xx、STM32F415xx/417xx、STM32F427xx/437xx、
    STM32F429xx/439xx、STM32F401xx/410xx/411xE、STM32F412xx、STM32F446xx 
    和 STM32F469xx/479xx 以及 STM32F413_423xx 器件上运行。

  - 该示例已在以下评估板/开发板上进行测试：STMicroelectronics 的
    STM324xG-EVAL（STM32F40xx/STM32F41xx 器件）、STM32F410xx-Nucleo RevC（STM32F410xx）、
    STM32F412G-Discovery RevC（STM32F412xx）、STM32F413H-DISCO revA（STM32F413_423xx）、
    STM32437I-EVAL（STM32F427xx/STM32F437xx 器件）、STM324x9I-EVAL RevB（STM32F429xx/STM32F439xx 器件）、
    STM32446E-EVAL RevB（STM32F446xx 器件）和 STM32F469I-EVAL RevB（STM32F469xx 器件）。
    该示例可以方便地针对其他受支持的器件和开发板进行定制。

@par 如何使用？

要使程序正常工作，请执行以下操作：

 + EWARM
    - 打开 `Template.eww` 工作区
    - 重建所有文件：Project -> Rebuild all
    - 加载工程镜像：Project -> Debug
    - 运行程序：Debug -> Go (F5)
 
 + MDK-ARM
    - 打开 `Template.uvprojx` 工程
    - 重建所有目标文件：Project -> Rebuild all target files
    - 加载工程镜像：Debug -> Start/Stop Debug Session
    - 运行程序：Debug -> Run (F5)
    
 + TrueSTUDIO
    - 打开 TrueSTUDIO 工具链。
    - 点击 File -> Switch Workspace -> Other 并浏览到 TrueSTUDIO 工作区目录。
    - 点击 File -> Import，选择 General -> "Existing Projects into Workspace"，然后点击 "Next"。
    - 浏览到 TrueSTUDIO 工作区目录并选择该项目。
    - 重建所有工程文件：在 "Project explorer" 窗口选择项目，然后点击 Project -> build project。
    - 运行程序：Run -> Debug (F11)
 + SW4STM32
    - 打开 SW4STM32 工具链。
    - 点击 File -> Switch Workspace -> Other 并浏览到 SW4STM32 工作区目录。
    - 点击 File -> Import，选择 General -> "Existing Projects into Workspace"，然后点击 "Next"。
    - 浏览到 SW4STM32 工作区目录并选择该项目。
    - 重建所有工程文件：在 "Project explorer" 窗口选择项目，然后点击 Project -> build project。
    - 运行程序：Run -> Debug (F11)

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
