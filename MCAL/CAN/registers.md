/*
*************** registers.md ***************
*  Author : Ammar Mohamed Hraga
*  layer  : ---
*/

RCC_AHB1ENR: بت لكل GPIO port، GPIOAEN (bit 0)، GPIOBEN (bit 1)، GPIOCEN (bit 2)، GPIODEN (bit 3). من غيرها الـ GPIO مش بيشتغل
RCC_APB1ENR: CAN1EN (bit 25)، CAN2EN (bit 26). CAN2 محتاج CAN1EN شغال كمان لأنه بيشاركه الـ filters

GPIOx_MODER: 2 بت لكل pin، 00 input، 01 output، 10 alternate function، 11 analog. للـ CAN لازم 10
GPIOx_OTYPER: بت لكل pin، 0 push-pull و 1 open-drain. للـ TX خليه 0
GPIOx_OSPEEDR: 2 بت لكل pin، سرعة الـ output. Fast كفاية
GPIOx_PUPDR: 2 بت لكل pin، 00 من غير، 01 pull-up، 10 pull-down. للـ RX خليه pull-up
GPIOx_AFRL: 4 بت لكل pin، للـ pins من 0 لـ 7
GPIOx_AFRH: 4 بت لكل pin، للـ pins من 8 لـ 15. الـ pin رقم n بيبدأ من bit (n-8)*4


CAN_MCR (offset 0x00):
INRQ (bit 0): طلب الدخول في init mode، لازم تكون فيه عشان تعدّل BTR والـ filters
SLEEP (bit 1): طلب sleep mode
TXFP (bit 2): ترتيب الإرسال، 1 حسب الأقدم و 0 حسب الـ ID
RFLM (bit 3): قفل الـ RX FIFO لما يتملي بدل ما يكتب فوق
NART (bit 4): 1 يعني من غير إعادة إرسال تلقائي
AWUM (bit 5): wakeup تلقائي
ABOM (bit 6): 1 يخلي الـ bus-off recovery تلقائي
TTCM (bit 7): time triggered mode
RESET (bit 15): ريسيت للـ CAN
DBF (bit 16): يوقف الـ CAN وقت الـ debug

CAN_MSR (offset 0x04):
INAK (bit 0): 1 يعني الـ CAN فعلاً دخل init mode (ده رد على INRQ)
SLAK (bit 1): 1 يعني فعلاً في sleep mode
ERRI (bit 2): حصل error interrupt
WKUI (bit 3): حصل wakeup
SLAKI (bit 4): دخل sleep
TXM / RXM (bit 8, 9): بيرسل / بيستقبل دلوقتي
SAMP (bit 10): آخر sample point
RX (bit 11): حالة خط RX


