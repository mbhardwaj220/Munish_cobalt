Devices.DevicesView=class extends UI.VBox{constructor(){super(true);this.registerRequiredCSS('devices/devicesView.css');this.contentElement.classList.add('devices-view');var hbox=this.contentElement.createChild('div','hbox devices-container');var sidebar=hbox.createChild('div','devices-sidebar');sidebar.createChild('div','devices-view-title').createTextChild(Common.UIString('Devices'));this._sidebarList=sidebar.createChild('div','devices-sidebar-list');this._discoveryView=new Devices.DevicesView.DiscoveryView();this._sidebarListSpacer=this._sidebarList.createChild('div','devices-sidebar-spacer');this._discoveryListItem=this._sidebarList.createChild('div','devices-sidebar-item');this._discoveryListItem.textContent=Common.UIString('Settings');this._discoveryListItem.addEventListener('click',this._selectSidebarListItem.bind(this,this._discoveryListItem,this._discoveryView));this._viewById=new Map();this._devices=[];this._listItemById=new Map();this._selectedListItem=null;this._visibleView=null;this._viewContainer=hbox.createChild('div','flex-auto vbox');var discoveryFooter=this.contentElement.createChild('div','devices-footer');this._deviceCountSpan=discoveryFooter.createChild('span');discoveryFooter.createChild('span').textContent=Common.UIString(' Read ');discoveryFooter.appendChild(UI.createExternalLink('https://developers.google.com/chrome-developer-tools/docs/remote-debugging',Common.UIString('remote debugging documentation')));discoveryFooter.createChild('span').textContent=Common.UIString(' for more information.');this._updateFooter();this._selectSidebarListItem(this._discoveryListItem,this._discoveryView);InspectorFrontendHost.events.addEventListener(InspectorFrontendHostAPI.Events.DevicesUpdated,this._devicesUpdated,this);InspectorFrontendHost.events.addEventListener(InspectorFrontendHostAPI.Events.DevicesDiscoveryConfigChanged,this._devicesDiscoveryConfigChanged,this);InspectorFrontendHost.events.addEventListener(InspectorFrontendHostAPI.Events.DevicesPortForwardingStatusChanged,this._devicesPortForwardingStatusChanged,this);this.contentElement.tabIndex=0;this.setDefaultFocusedElement(this.contentElement);}
static _instance(){if(!Devices.DevicesView._instanceObject)
Devices.DevicesView._instanceObject=new Devices.DevicesView();return Devices.DevicesView._instanceObject;}
_selectSidebarListItem(listItem,view){if(this._selectedListItem===listItem)
return;if(this._selectedListItem){this._selectedListItem.classList.remove('selected');this._visibleView.detach();}
this._visibleView=view;this._selectedListItem=listItem;this._visibleView.show(this._viewContainer);this._selectedListItem.classList.add('selected');}
_devicesUpdated(event){this._devices=(event.data).slice().filter(d=>d.adbSerial.toUpperCase()!=='WEBRTC'&&d.adbSerial.toUpperCase()!=='LOCALHOST');for(var device of this._devices){if(!device.adbConnected)
device.adbModel=Common.UIString('Unknown');}
var ids=new Set();for(var device of this._devices)
ids.add(device.id);var selectedRemoved=false;for(var deviceId of this._viewById.keys()){if(!ids.has(deviceId)){var listItem=(this._listItemById.get(deviceId));this._listItemById.remove(deviceId);this._viewById.remove(deviceId);listItem.remove();if(listItem===this._selectedListItem)
selectedRemoved=true;}}
for(var device of this._devices){var view=this._viewById.get(device.id);var listItem=this._listItemById.get(device.id);if(!view){view=new Devices.DevicesView.DeviceView();this._viewById.set(device.id,view);listItem=this._createSidebarListItem(view);this._listItemById.set(device.id,listItem);this._sidebarList.insertBefore(listItem,this._sidebarListSpacer);}
listItem._title.textContent=device.adbModel;listItem._status.textContent=device.adbConnected?Common.UIString('Connected'):Common.UIString('Pending Authorization');listItem.classList.toggle('device-connected',device.adbConnected);view.update(device);}
if(selectedRemoved)
this._selectSidebarListItem(this._discoveryListItem,this._discoveryView);this._updateFooter();}
_createSidebarListItem(view){var listItem=createElementWithClass('div','devices-sidebar-item');listItem.addEventListener('click',this._selectSidebarListItem.bind(this,listItem,view));listItem._title=listItem.createChild('div','devices-sidebar-item-title');listItem._status=listItem.createChild('div','devices-sidebar-item-status');return listItem;}
_devicesDiscoveryConfigChanged(event){var config=(event.data);this._discoveryView.discoveryConfigChanged(config);}
_devicesPortForwardingStatusChanged(event){var status=(event.data);for(var deviceId in status){var view=this._viewById.get(deviceId);if(view)
view.portForwardingStatusChanged(status[deviceId]);}
for(var deviceId of this._viewById.keys()){var view=this._viewById.get(deviceId);if(view&&!(deviceId in status))
view.portForwardingStatusChanged({ports:{},browserId:''});}}
_updateFooter(){this._deviceCountSpan.textContent=!this._devices.length?Common.UIString('No devices detected.'):this._devices.length===1?Common.UIString('1 device detected.'):Common.UIString('%d devices detected.',this._devices.length);}
wasShown(){super.wasShown();if(Runtime.queryParam('nodeFrontend'))
InspectorFrontendHost.setDevicesUpdatesEnabled(false);InspectorFrontendHost.setDevicesUpdatesEnabled(true);}
willHide(){super.wasShown();if(!Runtime.queryParam('nodeFrontend'))
InspectorFrontendHost.setDevicesUpdatesEnabled(false);}};Devices.DevicesView.DiscoveryView=class extends UI.VBox{constructor(){super();this.setMinimumSize(100,100);this.element.classList.add('discovery-view');this.contentElement.createChild('div','hbox device-text-row').createChild('div','view-title').textContent=Common.UIString('Settings');var discoverUsbDevicesCheckbox=UI.CheckboxLabel.create(Common.UIString('Discover USB devices'));discoverUsbDevicesCheckbox.classList.add('usb-checkbox');this.element.appendChild(discoverUsbDevicesCheckbox);this._discoverUsbDevicesCheckbox=discoverUsbDevicesCheckbox.checkboxElement;this._discoverUsbDevicesCheckbox.addEventListener('click',()=>{this._config.discoverUsbDevices=this._discoverUsbDevicesCheckbox.checked;InspectorFrontendHost.setDevicesDiscoveryConfig(this._config);},false);var help=this.element.createChild('div','discovery-help');help.createChild('span').textContent=Common.UIString('Need help? Read Chrome ');help.appendChild(UI.createExternalLink('https://developers.google.com/chrome-developer-tools/docs/remote-debugging',Common.UIString('remote debugging documentation.')));this._config;this._portForwardingView=new Devices.DevicesView.PortForwardingView((enabled,config)=>{this._config.portForwardingEnabled=enabled;this._config.portForwardingConfig={};for(var rule of config)
this._config.portForwardingConfig[rule.port]=rule.address;InspectorFrontendHost.setDevicesDiscoveryConfig(this._config);});this._portForwardingView.show(this.element);this._networkDiscoveryView=new Devices.DevicesView.NetworkDiscoveryView(false,(enabled,config)=>{this._config.networkDiscoveryEnabled=enabled;this._config.networkDiscoveryConfig=config;InspectorFrontendHost.setDevicesDiscoveryConfig(this._config);});this._networkDiscoveryView.show(this.element);}
discoveryConfigChanged(config){this._config=config;this._discoverUsbDevicesCheckbox.checked=config.discoverUsbDevices;this._portForwardingView.discoveryConfigChanged(config.portForwardingEnabled,config.portForwardingConfig);this._networkDiscoveryView.discoveryConfigChanged(config.networkDiscoveryEnabled,config.networkDiscoveryConfig);}};Devices.DevicesView.PortForwardingView=class extends UI.VBox{constructor(callback){super();this._callback=callback;this.element.classList.add('port-forwarding-view');var portForwardingHeader=this.element.createChild('div','port-forwarding-header');var portForwardingEnabledCheckbox=UI.CheckboxLabel.create(Common.UIString('Port forwarding'));portForwardingEnabledCheckbox.classList.add('port-forwarding-checkbox');portForwardingHeader.appendChild(portForwardingEnabledCheckbox);this._portForwardingEnabledCheckbox=portForwardingEnabledCheckbox.checkboxElement;this._portForwardingEnabledCheckbox.addEventListener('click',this._update.bind(this),false);var portForwardingFooter=this.element.createChild('div','port-forwarding-footer');portForwardingFooter.createChild('span').textContent=Common.UIString('Define the listening port on your device that maps to a port accessible from your development machine. ');portForwardingFooter.appendChild(UI.createExternalLink('https://developer.chrome.com/devtools/docs/remote-debugging#port-forwarding',Common.UIString('Learn more')));this._list=new UI.ListWidget(this);this._list.registerRequiredCSS('devices/devicesView.css');this._list.element.classList.add('port-forwarding-list');var placeholder=createElementWithClass('div','port-forwarding-list-empty');placeholder.textContent=Common.UIString('No rules');this._list.setEmptyPlaceholder(placeholder);this._list.show(this.element);this._editor=null;this.element.appendChild(UI.createTextButton(Common.UIString('Add rule'),this._addRuleButtonClicked.bind(this),'add-rule-button'));this._portForwardingConfig=[];}
_update(){this._callback.call(null,this._portForwardingEnabledCheckbox.checked,this._portForwardingConfig);}
_addRuleButtonClicked(){this._list.addNewItem(this._portForwardingConfig.length,{port:'',address:''});}
discoveryConfigChanged(portForwardingEnabled,portForwardingConfig){this._portForwardingEnabledCheckbox.checked=portForwardingEnabled;this._portForwardingConfig=[];this._list.clear();for(var key of Object.keys(portForwardingConfig)){var rule=({port:key,address:portForwardingConfig[key]});this._portForwardingConfig.push(rule);this._list.appendItem(rule,true);}}
renderItem(rule,editable){var element=createElementWithClass('div','port-forwarding-list-item');var port=element.createChild('div','port-forwarding-value port-forwarding-port');port.createChild('span','port-localhost').textContent=Common.UIString('localhost:');port.createTextChild(rule.port);element.createChild('div','port-forwarding-separator');element.createChild('div','port-forwarding-value').textContent=rule.address;return element;}
removeItemRequested(rule,index){this._portForwardingConfig.splice(index,1);this._list.removeItem(index);this._update();}
commitEdit(rule,editor,isNew){rule.port=editor.control('port').value.trim();rule.address=editor.control('address').value.trim();if(isNew)
this._portForwardingConfig.push(rule);this._update();}
beginEdit(rule){var editor=this._createEditor();editor.control('port').value=rule.port;editor.control('address').value=rule.address;return editor;}
_createEditor(){if(this._editor)
return this._editor;var editor=new UI.ListWidget.Editor();this._editor=editor;var content=editor.contentElement();var fields=content.createChild('div','port-forwarding-edit-row');fields.createChild('div','port-forwarding-value port-forwarding-port').appendChild(editor.createInput('port','text','Device port (3333)',portValidator.bind(this)));fields.createChild('div','port-forwarding-separator port-forwarding-separator-invisible');fields.createChild('div','port-forwarding-value').appendChild(editor.createInput('address','text','Local address (dev.example.corp:3333)',addressValidator));return editor;function portValidator(rule,index,input){var value=input.value.trim();var match=value.match(/^(\d+)$/);if(!match)
return false;var port=parseInt(match[1],10);if(port<1024||port>65535)
return false;for(var i=0;i<this._portForwardingConfig.length;++i){if(i!==index&&this._portForwardingConfig[i].port===value)
return false;}
return true;}
function addressValidator(rule,index,input){var match=input.value.trim().match(/^([a-zA-Z0-9\.\-_]+):(\d+)$/);if(!match)
return false;var port=parseInt(match[2],10);return port<=65535;}}};Devices.DevicesView.NetworkDiscoveryView=class extends UI.VBox{constructor(nodeFrontend,callback){super();this._nodeFrontend=nodeFrontend;this._callback=callback;this.element.classList.add('network-discovery-view');var networkDiscoveryHeader=this.element.createChild('div','network-discovery-header');var networkDiscoveryEnabledCheckbox=UI.CheckboxLabel.create(Common.UIString('Network targets'));networkDiscoveryEnabledCheckbox.classList.add('network-discovery-checkbox');networkDiscoveryHeader.appendChild(networkDiscoveryEnabledCheckbox);this._networkDiscoveryEnabledCheckbox=networkDiscoveryEnabledCheckbox.checkboxElement;this._networkDiscoveryEnabledCheckbox.disabled=!!Runtime.queryParam('nodeFrontend');this._networkDiscoveryEnabledCheckbox.checked=!!Runtime.queryParam('nodeFrontend');this._networkDiscoveryEnabledCheckbox.addEventListener('click',this._enabledCheckboxClicked.bind(this),false);var networkDiscoveryFooter=this.element.createChild('div','network-discovery-footer');if(nodeFrontend){networkDiscoveryFooter.createChild('span').textContent=Common.UIString('Specify network endpoint and DevTools will connect to it automatically. ');var link=networkDiscoveryFooter.createChild('span','link');link.textContent=Common.UIString('Learn more');link.addEventListener('click',()=>InspectorFrontendHost.openInNewTab('https://nodejs.org/en/docs/inspector/'));}else{networkDiscoveryFooter.createChild('span').textContent=Common.UIString('Define the target connection address');}
this._list=new UI.ListWidget(this);this._list.registerRequiredCSS('devices/devicesView.css');this._list.element.classList.add('network-discovery-list');var placeholder=createElementWithClass('div','network-discovery-list-empty');placeholder.textContent=nodeFrontend?Common.UIString('No connections specified'):Common.UIString('No addresses defined');this._list.setEmptyPlaceholder(placeholder);this._list.show(this.element);this._editor=null;var addButton=UI.createTextButton(nodeFrontend?Common.UIString('Add connection'):Common.UIString('Add address'),this._addNetworkTargetButtonClicked.bind(this),'add-network-target-button',true);this.element.appendChild(addButton);this._networkDiscoveryConfig=[];this._networkDiscoveryEnabled=false;if(nodeFrontend){this.element.classList.add('node-frontend');this._list.element.classList.add('node-frontend');}}
_update(){var config=this._networkDiscoveryConfig.map(item=>item.address);this._callback.call(null,this._networkDiscoveryEnabled,config);}
_addNetworkTargetButtonClicked(){this._list.addNewItem(this._networkDiscoveryConfig.length,{address:'',port:''});}
discoveryConfigChanged(networkDiscoveryEnabled,networkDiscoveryConfig){this._networkDiscoveryEnabled=networkDiscoveryEnabled;if(!Runtime.queryParam('nodeFrontend'))
this._networkDiscoveryEnabledCheckbox.checked=networkDiscoveryEnabled;this._networkDiscoveryConfig=[];this._list.clear();for(var address of networkDiscoveryConfig){var item={address:address,port:''};this._networkDiscoveryConfig.push(item);this._list.appendItem(item,true);}}
_enabledCheckboxClicked(){if(!Runtime.queryParam('nodeFrontend')){this._networkDiscoveryEnabled=this._networkDiscoveryEnabledCheckbox.checked;this._update();}}
renderItem(rule,editable){var element=createElementWithClass('div','network-discovery-list-item');element.createChild('div','network-discovery-value network-discovery-address').textContent=rule.address;return element;}
removeItemRequested(rule,index){this._networkDiscoveryConfig.splice(index,1);this._list.removeItem(index);this._update();}
commitEdit(rule,editor,isNew){rule.address=editor.control('address').value.trim();if(isNew)
this._networkDiscoveryConfig.push(rule);this._update();}
beginEdit(rule){var editor=this._createEditor();editor.control('address').value=rule.address;return editor;}
_createEditor(){if(this._editor)
return this._editor;var editor=new UI.ListWidget.Editor();this._editor=editor;var content=editor.contentElement();var fields=content.createChild('div','network-discovery-edit-row');var input=editor.createInput('address','text','Network address (e.g. localhost:9229)',addressValidator);fields.createChild('div','network-discovery-value network-discovery-address').appendChild(input);return editor;function addressValidator(rule,index,input){var match=input.value.trim().match(/^([a-zA-Z0-9\.\-_]+):(\d+)$/);if(!match)
return false;var port=parseInt(match[2],10);return port<=65535;}}};Devices.DevicesView.DeviceView=class extends UI.VBox{constructor(){super();this.setMinimumSize(100,100);this.contentElement.classList.add('device-view');var topRow=this.contentElement.createChild('div','hbox device-text-row');this._deviceTitle=topRow.createChild('div','view-title');this._deviceSerial=topRow.createChild('div','device-serial');this._portStatus=this.contentElement.createChild('div','device-port-status hidden');this._deviceOffline=this.contentElement.createChild('div');this._deviceOffline.textContent=Common.UIString('Pending authentication: please accept debugging session on the device.');this._noBrowsers=this.contentElement.createChild('div');this._noBrowsers.textContent=Common.UIString('No browsers detected.');this._browsers=this.contentElement.createChild('div','device-browser-list vbox');this._browserById=new Map();this._cachedPortStatus=null;this._device=null;}
update(device){if(!this._device||this._device.adbModel!==device.adbModel)
this._deviceTitle.textContent=device.adbModel;if(!this._device||this._device.adbSerial!==device.adbSerial)
this._deviceSerial.textContent='#'+device.adbSerial;this._deviceOffline.classList.toggle('hidden',device.adbConnected);this._noBrowsers.classList.toggle('hidden',!device.adbConnected||!!device.browsers.length);this._browsers.classList.toggle('hidden',!device.adbConnected||!device.browsers.length);var browserIds=new Set();for(var browser of device.browsers)
browserIds.add(browser.id);for(var browserId of this._browserById.keys()){if(!browserIds.has(browserId)){this._browserById.get(browserId).element.remove();this._browserById.remove(browserId);}}
for(var browser of device.browsers){var section=this._browserById.get(browser.id);if(!section){section=this._createBrowserSection();this._browserById.set(browser.id,section);this._browsers.appendChild(section.element);}
this._updateBrowserSection(section,browser);}
this._device=device;}
_createBrowserSection(){var element=createElementWithClass('div','vbox flex-none');var topRow=element.createChild('div','');var title=topRow.createChild('div','device-browser-title');var newTabRow=element.createChild('div','device-browser-new-tab');newTabRow.createChild('div','').textContent=Common.UIString('New tab:');var newTabInput=UI.createInput('','text');newTabRow.appendChild(newTabInput);newTabInput.placeholder=Common.UIString('Enter URL');newTabInput.addEventListener('keydown',newTabKeyDown,false);var newTabButton=UI.createTextButton(Common.UIString('Open'),openNewTab);newTabRow.appendChild(newTabButton);var pages=element.createChild('div','device-page-list vbox');var viewMore=element.createChild('div','device-view-more');viewMore.addEventListener('click',viewMoreClick,false);updateViewMoreTitle();var section={browser:null,element:element,title:title,pages:pages,viewMore:viewMore,newTab:newTabRow,pageSections:new Map()};return section;function viewMoreClick(){pages.classList.toggle('device-view-more-toggled');updateViewMoreTitle();}
function updateViewMoreTitle(){viewMore.textContent=pages.classList.contains('device-view-more-toggled')?Common.UIString('View less tabs\u2026'):Common.UIString('View more tabs\u2026');}
function newTabKeyDown(event){if(event.key==='Enter'){event.consume(true);openNewTab();}}
function openNewTab(){if(section.browser){InspectorFrontendHost.openRemotePage(section.browser.id,newTabInput.value.trim()||'about:blank');newTabInput.value='';}}}
_updateBrowserSection(section,browser){if(!section.browser||section.browser.adbBrowserName!==browser.adbBrowserName||section.browser.adbBrowserVersion!==browser.adbBrowserVersion){if(browser.adbBrowserVersion)
section.title.textContent=String.sprintf('%s (%s)',browser.adbBrowserName,browser.adbBrowserVersion);else
section.title.textContent=browser.adbBrowserName;}
var pageIds=new Set();for(var page of browser.pages)
pageIds.add(page.id);for(var pageId of section.pageSections.keys()){if(!pageIds.has(pageId)){section.pageSections.get(pageId).element.remove();section.pageSections.remove(pageId);}}
for(var index=0;index<browser.pages.length;++index){var page=browser.pages[index];var pageSection=section.pageSections.get(page.id);if(!pageSection){pageSection=this._createPageSection();section.pageSections.set(page.id,pageSection);section.pages.appendChild(pageSection.element);}
this._updatePageSection(pageSection,page);if(!index&&section.pages.firstChild!==pageSection.element)
section.pages.insertBefore(pageSection.element,section.pages.firstChild);}
var kViewMoreCount=3;for(var index=0,element=section.pages.firstChild;element;element=element.nextSibling,++index)
element.classList.toggle('device-view-more-page',index>=kViewMoreCount);section.viewMore.classList.toggle('device-needs-view-more',browser.pages.length>kViewMoreCount);section.newTab.classList.toggle('hidden',!browser.adbBrowserChromeVersion);section.browser=browser;}
_createPageSection(){var element=createElementWithClass('div','vbox');var titleRow=element.createChild('div','device-page-title-row');var title=titleRow.createChild('div','device-page-title');var inspect=UI.createTextButton(Common.UIString('Inspect'),doAction.bind(null,'inspect'));titleRow.appendChild(inspect);var toolbar=new UI.Toolbar('');toolbar.appendToolbarItem(new UI.ToolbarMenuButton(appendActions));titleRow.appendChild(toolbar.element);var url=element.createChild('div','device-page-url');var section={page:null,element:element,title:title,url:url,inspect:inspect};return section;function appendActions(contextMenu){contextMenu.defaultSection().appendItem(Common.UIString('Reload'),doAction.bind(null,'reload'));contextMenu.defaultSection().appendItem(Common.UIString('Focus'),doAction.bind(null,'activate'));contextMenu.defaultSection().appendItem(Common.UIString('Close'),doAction.bind(null,'close'));}
function doAction(action){if(section.page)
InspectorFrontendHost.performActionOnRemotePage(section.page.id,action);}}
_updatePageSection(section,page){if(!section.page||section.page.name!==page.name){section.title.textContent=page.name;section.title.title=page.name;}
if(!section.page||section.page.url!==page.url){section.url.textContent='';section.url.appendChild(UI.createExternalLink(page.url));}
section.inspect.disabled=page.attached;section.page=page;}
portForwardingStatusChanged(status){var json=JSON.stringify(status);if(json===this._cachedPortStatus)
return;this._cachedPortStatus=json;this._portStatus.removeChildren();this._portStatus.createChild('div','device-port-status-text').textContent=Common.UIString('Port Forwarding:');var connected=[];var transient=[];var error=[];var empty=true;for(var port in status.ports){if(!status.ports.hasOwnProperty(port))
continue;empty=false;var portStatus=status.ports[port];var portNumber=createElementWithClass('div','device-view-port-number monospace');portNumber.textContent=':'+port;if(portStatus>=0)
this._portStatus.appendChild(portNumber);else
this._portStatus.insertBefore(portNumber,this._portStatus.firstChild);var portIcon=createElementWithClass('div','device-view-port-icon');if(portStatus>=0){connected.push(port);}else if(portStatus===-1||portStatus===-2){portIcon.classList.add('device-view-port-icon-transient');transient.push(port);}else if(portStatus<0){portIcon.classList.add('device-view-port-icon-error');error.push(port);}
this._portStatus.insertBefore(portIcon,portNumber);}
var title=[];if(connected.length)
title.push(Common.UIString('Connected: %s',connected.join(', ')));if(transient.length)
title.push(Common.UIString('Transient: %s',transient.join(', ')));if(error.length)
title.push(Common.UIString('Error: %s',error.join(', ')));this._portStatus.title=title.join('; ');this._portStatus.classList.toggle('hidden',empty);}};Devices.DevicesView.BrowserSection;Devices.DevicesView.PageSection;Devices.DevicesView.Panel=class extends UI.Panel{constructor(){super('node-connection');this.registerRequiredCSS('devices/devicesView.css');this.contentElement.classList.add('devices-view-panel');var container=this.contentElement.createChild('div','devices-view-panel-center');var image=container.createChild('img','devices-view-panel-logo');image.src='https://nodejs.org/static/images/logos/nodejs-new-pantone-black.png';InspectorFrontendHost.events.addEventListener(InspectorFrontendHostAPI.Events.DevicesDiscoveryConfigChanged,this._devicesDiscoveryConfigChanged,this);this._config;this.contentElement.tabIndex=0;this.setDefaultFocusedElement(this.contentElement);InspectorFrontendHost.setDevicesUpdatesEnabled(false);InspectorFrontendHost.setDevicesUpdatesEnabled(true);this._networkDiscoveryView=new Devices.DevicesView.NetworkDiscoveryView(true,(enabled,config)=>{this._config.networkDiscoveryEnabled=enabled;this._config.networkDiscoveryConfig=config;InspectorFrontendHost.setDevicesDiscoveryConfig(this._config);});this._networkDiscoveryView.show(container);}
_devicesDiscoveryConfigChanged(event){this._config=(event.data);this._networkDiscoveryView.discoveryConfigChanged(this._config.networkDiscoveryEnabled,this._config.networkDiscoveryConfig);}};;Runtime.cachedResources["devices/devicesView.css"]="/*\n * Copyright (c) 2015 The Chromium Authors. All rights reserved.\n * Use of this source code is governed by a BSD-style license that can be\n * found in the LICENSE file.\n */\n\n.devices-container {\n    overflow: hidden;\n    flex: auto;\n}\n\n.devices-sidebar {\n    flex: 0 0 150px;\n    display: flex;\n    flex-direction: column;\n    align-items: stretch;\n    padding-top: 15px;\n}\n\n.devices-sidebar-list {\n    flex: none;\n    display: flex;\n    flex-direction: column;\n    align-items: stretch;\n}\n\n.devices-sidebar-item {\n    color: #222 !important;\n    padding: 6px 6px 6px 16px;\n    flex: auto;\n    display: flex;\n    flex-direction: column;\n    justify-content: center;\n    font-size: 14px;\n}\n\n.devices-sidebar-item.selected {\n    border-left: 6px solid #666 !important;\n    padding-left: 10px;\n}\n\n.devices-sidebar-item-status:before {\n    content: \"\\25cf\";\n    font-size: 16px;\n    color: red;\n    position: relative;\n    top: 1px;\n    margin-right: 2px;\n}\n\n.devices-sidebar-item.device-connected .devices-sidebar-item-status:before {\n    color: green;\n}\n\n.devices-sidebar-spacer {\n    flex: none;\n}\n\n.devices-view-title {\n    font-size: 16px;\n    margin: 0 0 15px 15px;\n    padding-top: 1px;\n}\n\n.view-title {\n    font-size: 16px;\n    flex: none;\n}\n\n.devices-footer {\n    border-top: 1px solid #cdcdcd;\n    background-color: #f3f3f3;\n    flex: none;\n    padding: 3px 10px;\n    overflow: hidden;\n}\n\n.devices-footer > span {\n    white-space: pre;\n}\n\n.discovery-view {\n    overflow-x: hidden;\n    overflow-y: auto;\n    padding: 15px 15px 0px 0px;\n}\n\n.discovery-view > * {\n    flex: none;\n}\n\n.usb-checkbox {\n    padding-bottom: 8px;\n    margin-top: 20px;\n}\n\n.port-forwarding-header {\n    display: flex;\n    align-items: center;\n    flex-direction: row;\n    margin-top: 5px;\n}\n\n.add-rule-button {\n    margin: 10px 25px;\n    align-self: flex-start;\n}\n\n.discovery-help {\n    margin: 5px 0 25px 25px;\n}\n\n.discovery-help > span {\n    white-space: pre;\n}\n\n.port-forwarding-list {\n    margin: 10px 0 0 25px;\n    max-width: 500px;\n    flex: none;\n}\n\n.port-forwarding-list-empty {\n    flex: auto;\n    height: 30px;\n    display: flex;\n    align-items: center;\n    justify-content: center;\n}\n\n.port-forwarding-list-item {\n    padding: 3px 5px 3px 5px;\n    height: 30px;\n    display: flex;\n    align-items: center;\n    position: relative;\n    flex: auto 1 1;\n}\n\n.list-item .port-forwarding-value {\n    white-space: nowrap;\n    text-overflow: ellipsis;\n    -webkit-user-select: none;\n    color: #222;\n    overflow: hidden;\n}\n\n.port-forwarding-value {\n    flex: 3 1 0;\n}\n\n.port-forwarding-value.port-forwarding-port {\n    flex: 1 1 0;\n}\n\n.port-localhost {\n    color: #aaa;\n}\n\n.port-forwarding-separator {\n    flex: 0 0 1px;\n    background-color: rgb(231, 231, 231);\n    height: 30px;\n    margin: 0 4px;\n}\n\n.port-forwarding-separator-invisible {\n    visibility: hidden;\n    height: 100% !important;\n}\n\n.port-forwarding-edit-row {\n    flex: none;\n    display: flex;\n    flex-direction: row;\n    margin: 6px 5px;\n    align-items: center;\n}\n\n.port-forwarding-edit-row input {\n    width: 100%;\n    text-align: inherit;\n}\n\n.port-forwarding-footer {\n    overflow: hidden;\n    margin: 15px 0 0 25px;\n    max-width: 500px;\n}\n\n.port-forwarding-footer > * {\n    white-space: pre-wrap;\n}\n\n.network-discovery-header {\n    display: flex;\n    align-items: center;\n    flex-direction: row;\n    margin-top: 5px;\n}\n\n.add-network-target-button {\n    margin: 10px 25px;\n    align-self: flex-start;\n}\n\n.network-discovery-list {\n    margin: 10px 0 0 25px;\n    max-width: 500px;\n    flex: none;\n}\n\n.network-discovery-list-empty {\n    flex: auto;\n    height: 30px;\n    display: flex;\n    align-items: center;\n    justify-content: center;\n}\n\n.network-discovery-list-item {\n    padding: 3px 5px 3px 5px;\n    height: 30px;\n    display: flex;\n    align-items: center;\n    position: relative;\n    flex: auto 1 1;\n}\n\n.list-item .network-discovery-value {\n    white-space: nowrap;\n    text-overflow: ellipsis;\n    -webkit-user-select: none;\n    color: #222;\n    overflow: hidden;\n}\n\n.network-discovery-value {\n    flex: 3 1 0;\n}\n\n.network-discovery-edit-row {\n    flex: none;\n    display: flex;\n    flex-direction: row;\n    margin: 6px 5px;\n    align-items: center;\n}\n\n.network-discovery-edit-row input {\n    width: 100%;\n    text-align: inherit;\n}\n\n.network-discovery-footer {\n    overflow: hidden;\n    margin: 15px 0 0 25px;\n    max-width: 500px;\n}\n\n.network-discovery-footer > * {\n    white-space: pre-wrap;\n}\n\n.device-view {\n    overflow: auto;\n    -webkit-user-select: text;\n    flex: auto;\n}\n\n.device-text-row {\n    align-items: baseline;\n    margin-right: 25px;\n}\n\n.device-serial {\n    color: #777;\n    margin-left: 5px;\n    flex: none;\n}\n\n.device-browser-list {\n    flex: auto;\n    overflow: auto;\n    padding-right: 10px;\n    margin-top: 30px;\n}\n\n.device-browser-list > div {\n    margin-bottom: 15px;\n}\n\n.device-browser-title {\n    font-size: 16px;\n}\n\n.device-browser-new-tab {\n    display: flex;\n    flex-direction: row;\n    align-items: center;\n    margin: 10px 0 0 10px;\n}\n\n.device-browser-new-tab > div {\n    font-size: 13px;\n}\n\n.device-browser-new-tab > input {\n    margin: 0 10px;\n}\n\n.device-page-list {\n    margin: 10px 0 0 10px;\n    overflow-x: auto;\n    align-items: stretch;\n    flex: none;\n}\n\n.device-page-list > div {\n    flex: none;\n    padding: 5px 0;\n}\n\n.device-page-list:not(.device-view-more-toggled) > div.device-view-more-page {\n    display: none;\n}\n\n.device-page-title-row {\n    display: flex;\n    flex-direction: row;\n    align-items: center;\n}\n\n.device-page-title {\n    font-size: 15px;\n    flex: auto;\n    white-space: nowrap;\n    text-overflow: ellipsis;\n    overflow: hidden;\n}\n\n.device-page-title-row .toolbar {\n    margin-left: 3px;\n    padding: 0;\n    border-radius: 3px;\n}\n\n.device-page-title-row .toolbar:hover {\n    background-color: hsl(0, 0%, 90%);\n}\n\n.device-page-url {\n    margin: 3px 100px 3px 0;\n}\n\n.device-page-url a {\n    color: #777;\n    word-break: break-all;\n}\n\n.device-view-more {\n    cursor: pointer;\n    text-decoration: underline;\n    color: rgb(17, 85, 204);\n    margin: 5px 0 0 10px;\n    display: none;\n}\n\n.device-view-more.device-needs-view-more  {\n    display: block;\n}\n\n.device-port-status {\n    overflow: hidden;\n    flex: none;\n    display: flex;\n    align-items: baseline;\n    margin: 10px 0 0 10px;\n}\n\n.device-port-status-text {\n    margin-right: 10px;\n}\n\n.device-view-port-icon {\n    background-color: green;\n    border: 0 solid transparent;\n    border-radius: 6px;\n    height: 12px;\n    width: 12px;\n    position: relative;\n    top: 2px;\n    flex: none;\n}\n\n.device-view-port-number {\n    margin: 0 10px 0 2px;\n    flex: none;\n}\n\n.device-view-port-icon.device-view-port-icon-error {\n    background-color: red;\n}\n\n.device-view-port-icon.device-view-port-icon-transient {\n    transform: scale(1.2);\n    background-color: orange;\n}\n\n.node-frontend .network-discovery-header {\n    display: none;\n}\n\n.devices-view-panel {\n    align-items: center;\n    justify-content: flex-start;\n}\n\n.node-frontend.network-discovery-view {\n    min-width: 400px;\n    flex: auto;\n}\n\n.node-frontend .add-network-target-button {\n    align-self: center;\n}\n\n:host-context(.node-frontend) .network-discovery-list-empty {\n    height: 40px;\n}\n\n:host-context(.node-frontend) .network-discovery-list-item {\n    padding: 3px 15px;\n    height: 40px;\n}\n\n.node-frontend .network-discovery-list {\n    margin: 20px 0 5px 0;\n    max-width: 600px;\n    max-height: 202px;\n}\n\n.node-frontend .network-discovery-footer {\n    margin: 0;\n}\n\n.devices-view-panel-center {\n    display: flex;\n    align-items: stretch;\n    justify-content: center;\n    max-width: 600px;\n    flex-direction: column;\n    padding-top: 50px;\n}\n\n.devices-view-panel-logo {\n    align-self: center;\n    width: 400px;\n    margin-bottom: 50px;\n    flex: none;\n}\n\n:host-context(.node-frontend) .network-discovery-edit-row input {\n    height: 30px;\n    padding-left: 5px;\n}\n\n:host-context(.node-frontend) .network-discovery-edit-row {\n    margin: 6px 9px;\n}\n\n/*# sourceURL=devices/devicesView.css */";