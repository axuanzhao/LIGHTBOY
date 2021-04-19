#ifndef __THREAD_WEB_HANDLER_H
#define __THREAD_WEB_HANDLER_H

#include <stdlib.h>
#include <wiringPi.h>
#include "config_loader.h"
#include "mongoose.h"

/**
 * This thread handles web events from the frontend UI.
 *
 * @author Darran Zhang @ codelast.com
 */

using namespace std;

extern CConfigLoader gConfigLoader;
static struct mg_serve_http_opts httpServerOpts;

/**
 * Send a http 302 response.
 *
 */
static void sendHttpResponse302(struct mg_connection *nc) {
  mg_printf(nc, "%s", "HTTP/1.1 302 OK\r\nLocation: /\r\n\r\n");
}

/**
 * A specific HTTP event handler to get light running mode.
 *
 * @param nc  Describes a HTTP connection.
 */
static void handleGetMode(struct mg_connection *nc) {
  int mode = MODE_AUTO;
  if (gConfigLoader.isManualMode()) {
    mode = (gConfigLoader.getLedLevel() == HIGH) ? MODE_ON : MODE_OFF;
  }
  LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Mode read: " << mode;

  // use chunked encoding in order to avoid calculating Content-Length, please refer to https://en.wikipedia.org/wiki/Chunked_transfer_encoding for details
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // output JSON object
  mg_printf_http_chunk(nc, "{ \"result\": \"%d\" }", mode);

  // send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

/**
 * A specific HTTP event handler to set light running mode.
 *
 */
static void handleSetMode(struct mg_connection *nc, struct http_message *hm) {
  /* get web page variables */
  int length = 8;
  char temp[length];
  memset(temp, 0, length);
  mg_get_http_var(&hm->body, "mode", temp, length);

  bool success = true;
  int mode = atoi(temp);
  switch (mode) {
  case MODE_ON:
    {
      LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Switch to mode ON";
      gConfigLoader.setManualMode(true);
      gConfigLoader.setLedLevel(HIGH);
      break;
    }
  case MODE_OFF:
    {
      LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Switch to mode OFF";
      gConfigLoader.setManualMode(true);
      gConfigLoader.setLedLevel(LOW);
      break;
    }
  case MODE_AUTO:
    {
      LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Switch to mode AUTO";
      gConfigLoader.setManualMode(false);
      break;
    }
  default:
    {
      LOG(ERROR) << CUtil::getCurrentDate() << "\t" << "Unrecognized mode: " << mode;
      success = false;
    }
  }

  if (success) {
    sendHttpResponse302(nc);
  }
}

/**
 * A specific HTTP event handler to get time range data.
 *
 * @param nc  Describes a HTTP connection.
 */
static void handleGetTimeRange(struct mg_connection *nc) {
  /* read time range data from memory */
  vector<string> vec;
  gConfigLoader.translateTimeRange2String(vec, " ");
  vector<string>::const_iterator it;
  string allTimeRangeStr;
  for (it = vec.begin(); it != vec.end(); it++) {
    allTimeRangeStr += *it + ",";
  }
  if (!allTimeRangeStr.empty()) {
    allTimeRangeStr = allTimeRangeStr.substr(0, allTimeRangeStr.length() - 1);
  }
  LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Time range read: " << allTimeRangeStr;

  // use chunked encoding in order to avoid calculating Content-Length, please refer to https://en.wikipedia.org/wiki/Chunked_transfer_encoding for details
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // output JSON object
  mg_printf_http_chunk(nc, "{ \"result\": \"%s\" }", allTimeRangeStr.c_str());

  // send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

/**
 * A specific HTTP event handler to save time range data from web UI to backend.
 *
 * @param nc  Describes a HTTP connection.
 */
static void handleSaveTimeRange(struct mg_connection *nc, struct http_message *hm) {
  /* get web page variables */
  int length = 1024;
  char temp[length];
  memset(temp, 0, length);
  mg_get_http_var(&hm->body, "str", temp, length);

  LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Time range data from web UI: [" << temp << "]";
  
  /* update the time range data in memory & config file */
  string timeRangeStr(temp);
  if (gConfigLoader.updateTimeRange(timeRangeStr)) {
    sendHttpResponse302(nc);
  }
}

/**
 * HTTP event handler.
 * Please refer to the API doc of Mongoose for the detail of the params.
 *
 */
static void httpEventHandler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
      if (mg_vcmp(&hm->uri, "/get-mode") == 0) {
	LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Will get mode...";
	handleGetMode(nc);
      } else if (mg_vcmp(&hm->uri, "/set-mode") == 0) {
	handleSetMode(nc, hm);
      } else if (mg_vcmp(&hm->uri, "/get-time-range") == 0) {
	LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Will get time range...";
        handleGetTimeRange(nc);
      } else if (mg_vcmp(&hm->uri, "/save-time-range") == 0) {
	LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Will save time range...";
	handleSaveTimeRange(nc, hm);
      } else {
        mg_serve_http(nc, hm, httpServerOpts);  // serve static content
      }
      break;
    default:
      break;
  }
}

void* threadWebHandler(void*) {
  char listenPort[8];
  memset(listenPort, 0, sizeof(listenPort));
  sprintf(listenPort, "%d", gConfigLoader.getListenPort());

  struct mg_mgr mgr;
  struct mg_connection *nc;

  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, listenPort, httpEventHandler);
  if (NULL == nc) {
    LOG(ERROR) <<  CUtil::getCurrentDate() << "\t" << "Cannot bind to " << listenPort;
    return NULL;
  }

  /* set up web server parameters */
  mg_set_protocol_http_websocket(nc);

  if (!CUtil::isDirExist(gConfigLoader.getWebRootPath())) {
    LOG(ERROR) << CUtil::getCurrentDate() << "\t" << "Cannot find web root directory, web handler thread exits";
    return NULL;
  }
  httpServerOpts.document_root = gConfigLoader.getWebRootPath();  // set up web root directory

  LOG(INFO) << CUtil::getCurrentDate() << "\t" << "Start web server on port [" << gConfigLoader.getListenPort() << "]";

  while (gConfigLoader.getThreadRunning()) {
    mg_mgr_poll(&mgr, 1000);
  }

  /* cleanup */
  mg_mgr_free(&mgr);

  return NULL;
}

#endif
