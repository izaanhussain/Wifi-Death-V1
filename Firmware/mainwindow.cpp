#include "mainwindow.h"

static int selected_network_index = -1;

Mainwindow::Mainwindow()
{
  display_ = new Display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_RESET, SCREEN_ADDRESS, SDA_PIN, SCL_PIN);
  w_utils_ = new WiFi_Utils(SET_RANDOM_MAC);
  buttons_ = new Buttons(BUTTON_SEL_PIN, BUTTON_BACK_PIN, BUTTON_UP_PIN, BUTTON_DOWN_PIN);
}

Mainwindow::~Mainwindow()
{
  delete display_;
  delete w_utils_;
  delete buttons_;
}

void Mainwindow::init()
{
  display_->startDisplay();

  display_->setDisplayText("WiFi Death V1", 0, 0, 1);
  display_->appendDisplayText("dev-izaan", 0, 1, 1);
  display_->appendDisplayText("Starting...", 0, 2, 1);

  if (SET_RANDOM_MAC)
    display_->appendDisplayText("Changing MAC...", 0, 3, 1);

  w_utils_->init();

  if (w_utils_->isInit)
  {
    display_->appendDisplayText("MAC:", 0, 4, 1);
    display_->appendDisplayText(w_utils_->macAddress(), 4, 4, 1);
    display_->appendDisplayText("Scanning...", 0, 5, 1);

    w_utils_->wifi_list = w_utils_->scanWifiList();
  }

  buttons_->init();

  page = 0;
  cursor_index = 0;
  on_page = false;
  on_wifi_scan_info = false;

  setMainPage();
}

void Mainwindow::loop()
{
  int num = buttons_->readButtons();

  switch (page)
  {
    case 0:
      handleMainPage(num);
      break;

    case 1:
    case 2:
    case 3:
      handleScanPage(num);
      break;

    case 4:
      handleInfoPage(num);
      break;

    default:
      page = 0;
      cursor_index = 0;
      setMainPage();
      break;
  }
}

void Mainwindow::handleBack()
{
  page = 0;
  cursor_index = 0;
  on_page = false;
  on_wifi_scan_info = false;

  setMainPage();
}

void Mainwindow::handleMainPage(int button)
{
  switch (button)
  {
    case 0:
      handleMainPageSel();
      break;

    case 1:
      handleMainPageBack();
      break;

    case 2:
      handleMainPageUp();
      break;

    case 3:
      handleMainPageDown();
      break;

    default:
      break;
  }
}

void Mainwindow::setMainPage()
{
  display_->setDisplayText("WiFi Death V1", 0, 0, 1);

  display_->appendDisplayText("1. Select", 2, 2, 1);
  display_->appendDisplayText("2. Scan", 2, 3, 1);
  display_->appendDisplayText("3. Attack", 2, 4, 1);
  display_->appendDisplayText("4. Info", 2, 5, 1);

  display_->appendDisplayText("*", 0, cursor_index + 2, 1);
}

void Mainwindow::handleMainPageUp()
{
  if (cursor_index == 0)
    cursor_index = 3;
  else
    cursor_index--;

  setMainPage();
}

void Mainwindow::handleMainPageDown()
{
  if (cursor_index == 3)
    cursor_index = 0;
  else
    cursor_index++;

  setMainPage();
}

void Mainwindow::handleMainPageSel()
{
  switch (cursor_index)
  {
    case 0:
      cursor_index = 0;
      setSelectPage();
      break;

    case 1:
      cursor_index = 0;
      on_wifi_scan_info = false;
      setScanPage();
      break;

    case 2:
      cursor_index = 0;
      setAttackPage();
      break;

    case 3:
      cursor_index = 0;
      setInfoPage();
      break;
  }
}

void Mainwindow::handleMainPageBack()
{
  return;
}

void Mainwindow::handleScanPage(int button)
{
  if (page == 3)
  {
    if (button == 1)
    {
      handleBack();
      return;
    }

    if (button == 0)
    {
      setAttackPage();
      return;
    }

    return;
  }

  if (on_wifi_scan_info)
  {
    if (button == 0 || button == 1)
    {
      on_wifi_scan_info = false;
      setScanPage();
    }

    return;
  }

  if (page == 1)
  {
    switch (button)
    {
      case 0:
        if (w_utils_->wifi_list.num > 0)
        {
          selected_network_index = cursor_index;
          setAttackPage();
        }
        break;

      case 1:
        handleBack();
        break;

      case 2:
        if (w_utils_->wifi_list.num > 0)
        {
          if (cursor_index == 0)
            cursor_index = w_utils_->wifi_list.num - 1;
          else
            cursor_index--;
        }

        setSelectPage();
        break;

      case 3:
        if (w_utils_->wifi_list.num > 0)
        {
          cursor_index++;

          if (cursor_index >= w_utils_->wifi_list.num)
            cursor_index = 0;
        }

        setSelectPage();
        break;
    }

    return;
  }

  switch (button)
  {
    case 0:
      handleScanPageSel();
      break;

    case 1:
      handleBack();
      break;

    case 2:
      handleScanPageUp();
      break;

    case 3:
      handleScanPageDown();
      break;

    default:
      break;
  }
}

void Mainwindow::setScanPage()
{
  page = 2;
  on_page = true;

  display_->setDisplayText("Scan", 0, 0, 1);

  if (w_utils_->wifi_list.num <= 0)
  {
    display_->appendDisplayText("No networks", 1, 2, 1);
    display_->appendDisplayText("SEL: Rescan", 1, 4, 1);
    return;
  }

  display_->appendDisplayText(w_utils_->wifi_list.num, 0, 0, 1);
  display_->appendDisplayText(" networks", 3, 0, 1);

  if (cursor_index == 0)
  {
    display_->appendDisplayText("* RESCAN", 0, 1, 1);

    for (int i = 0; i < w_utils_->wifi_list.num && i < 5; ++i)
    {
      std::string line =
        std::to_string(i + 1) + ". " +
        w_utils_->wifi_list.ssid[i];

      display_->appendDisplayText(line, 1, i + 2, 1);
    }
  }
  else
  {
    int network_index = cursor_index - 1;

    if (network_index >= w_utils_->wifi_list.num)
      network_index = w_utils_->wifi_list.num - 1;

    display_->appendDisplayText(
      "* " + w_utils_->wifi_list.ssid[network_index],
      0,
      1,
      1
    );

    int start = network_index;

    for (int row = 2; row < 7 && start < w_utils_->wifi_list.num; ++row, ++start)
    {
      std::string line =
        std::to_string(start + 1) + ". " +
        w_utils_->wifi_list.ssid[start];

      display_->appendDisplayText(line, 1, row, 1);
    }
  }
}

void Mainwindow::handleScanPageUp()
{
  int max_cursor = w_utils_->wifi_list.num;

  if (max_cursor <= 0)
  {
    cursor_index = 0;
    setScanPage();
    return;
  }

  if (cursor_index == 0)
    cursor_index = max_cursor;
  else
    cursor_index--;

  setScanPage();
}

void Mainwindow::handleScanPageDown()
{
  int max_cursor = w_utils_->wifi_list.num;

  if (max_cursor <= 0)
  {
    cursor_index = 0;
    setScanPage();
    return;
  }

  if (cursor_index >= max_cursor)
    cursor_index = 0;
  else
    cursor_index++;

  setScanPage();
}

void Mainwindow::handleScanPageSel()
{
  if (w_utils_->wifi_list.num <= 0)
  {
    display_->setDisplayText("Scanning...", 0, 2, 1);

    w_utils_->wifi_list = w_utils_->scanWifiList();

    cursor_index = 0;
    setScanPage();
    return;
  }

  if (cursor_index == 0)
  {
    display_->setDisplayText("Scanning...", 0, 2, 1);

    w_utils_->wifi_list = w_utils_->scanWifiList();

    cursor_index = 0;
    on_wifi_scan_info = false;

    setScanPage();
    return;
  }

  int network_index = cursor_index - 1;

  if (network_index < 0 ||
      network_index >= w_utils_->wifi_list.num)
    return;

  selected_network_index = network_index;

  display_->setDisplayText("SSID:", 0, 0, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.ssid[network_index],
    0,
    1,
    1
  );

  display_->appendDisplayText("BSSID:", 0, 2, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.bssid[network_index],
    0,
    3,
    1
  );

  display_->appendDisplayText("Channel:", 0, 4, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.channel[network_index],
    0,
    5,
    1
  );

  display_->appendDisplayText("Signal:", 0, 6, 1);
  display_->appendDisplayTextF(
    w_utils_->wifi_list.signal[network_index],
    0,
    7,
    1
  );

  on_wifi_scan_info = true;
}

void Mainwindow::setSelectPage()
{
  page = 1;
  on_page = true;
  on_wifi_scan_info = false;

  display_->setDisplayText("Select", 0, 0, 1);

  if (w_utils_->wifi_list.num <= 0)
  {
    display_->appendDisplayText("No networks", 1, 2, 1);
    display_->appendDisplayText("BACK", 1, 5, 1);
    return;
  }

  if (cursor_index >= w_utils_->wifi_list.num)
    cursor_index = 0;

  int start = cursor_index;

  for (int row = 1;
       row < 8 && start < w_utils_->wifi_list.num;
       ++row, ++start)
  {
    std::string prefix =
      start == cursor_index ? "* " : "  ";

    std::string line =
      prefix +
      std::to_string(start + 1) +
      ". " +
      w_utils_->wifi_list.ssid[start];

    display_->appendDisplayText(line, 0, row, 1);
  }
}

void Mainwindow::setAttackPage()
{
  page = 3;
  on_page = true;
  on_wifi_scan_info = false;

  display_->setDisplayText("Attack", 0, 0, 1);

  if (selected_network_index < 0 ||
      selected_network_index >= w_utils_->wifi_list.num)
  {
    display_->appendDisplayText("No target selected", 0, 2, 1);
    display_->appendDisplayText("Use Select first", 0, 4, 1);
    display_->appendDisplayText("BACK", 0, 7, 1);
    return;
  }

  int i = selected_network_index;

  display_->appendDisplayText("Target:", 0, 1, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.ssid[i],
    0,
    2,
    1
  );

  display_->appendDisplayText("BSSID:", 0, 3, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.bssid[i],
    0,
    4,
    1
  );

  display_->appendDisplayText("CH:", 0, 5, 1);
  display_->appendDisplayText(
    w_utils_->wifi_list.channel[i],
    4,
    5,
    1
  );

  display_->appendDisplayText("BACK", 0, 7, 1);
}

void Mainwindow::handleInfoPage(int button)
{
  if (button == 0 || button == 1)
    handleBack();
}

void Mainwindow::setInfoPage()
{
  cursor_index = 0;
  page = 4;
  on_page = true;
  on_wifi_scan_info = false;

  display_->setDisplayText("WiFi Death V1", 0, 0, 1);
  display_->appendDisplayText("dev-izaan", 0, 1, 1);
  display_->appendDisplayText("MAC:", 0, 2, 1);
  display_->appendDisplayText(
    w_utils_->macAddress(),
    4,
    2,
    1
  );
  display_->appendDisplayText("BACK", 0, 6, 1);
}