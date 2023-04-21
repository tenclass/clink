#pragma once

#define CUDA_VERSION 12010

/* CUDA Driver API 12.1 */
#define CUGETERRORSTRING 0
#define CUGETERRORNAME 1
#define CUINIT 2
#define CUDRIVERGETVERSION 3
#define CUDEVICEGET 4
#define CUDEVICEGETCOUNT 5
#define CUDEVICEGETNAME 6
#define CUDEVICEGETUUID 7
#define CUDEVICEGETUUID_V2 8
#define CUDEVICEGETLUID 9
#define CUDEVICETOTALMEM 10
#define CUDEVICEGETTEXTURE1DLINEARMAXWIDTH 11
#define CUDEVICEGETATTRIBUTE 12
#define CUDEVICEGETNVSCISYNCATTRIBUTES 13
#define CUDEVICESETMEMPOOL 14
#define CUDEVICEGETMEMPOOL 15
#define CUDEVICEGETDEFAULTMEMPOOL 16
#define CUDEVICEGETEXECAFFINITYSUPPORT 17
#define CUFLUSHGPUDIRECTRDMAWRITES 18
#define CUDEVICEGETPROPERTIES 19
#define CUDEVICECOMPUTECAPABILITY 20
#define CUDEVICEPRIMARYCTXRETAIN 21
#define CUDEVICEPRIMARYCTXRELEASE 22
#define CUDEVICEPRIMARYCTXSETFLAGS 23
#define CUDEVICEPRIMARYCTXGETSTATE 24
#define CUDEVICEPRIMARYCTXRESET 25
#define CUCTXCREATE 26
#define CUCTXCREATE_V3 27
#define CUCTXDESTROY 28
#define CUCTXPUSHCURRENT 29
#define CUCTXPOPCURRENT 30
#define CUCTXSETCURRENT 31
#define CUCTXGETCURRENT 32
#define CUCTXGETDEVICE 33
#define CUCTXGETFLAGS 34
#define CUCTXSETFLAGS 35
#define CUCTXGETID 36
#define CUCTXSYNCHRONIZE 37
#define CUCTXSETLIMIT 38
#define CUCTXGETLIMIT 39
#define CUCTXGETCACHECONFIG 40
#define CUCTXSETCACHECONFIG 41
#define CUCTXGETSHAREDMEMCONFIG 42
#define CUCTXSETSHAREDMEMCONFIG 43
#define CUCTXGETAPIVERSION 44
#define CUCTXGETSTREAMPRIORITYRANGE 45
#define CUCTXRESETPERSISTINGL2CACHE 46
#define CUCTXGETEXECAFFINITY 47
#define CUCTXATTACH 48
#define CUCTXDETACH 49
#define CUMODULELOAD 50
#define CUMODULELOADDATA 51
#define CUMODULELOADDATAEX 52
#define CUMODULELOADFATBINARY 53
#define CUMODULEUNLOAD 54
#define CUMODULEGETLOADINGMODE 55
#define CUMODULEGETFUNCTION 56
#define CUMODULEGETGLOBAL 57
#define CULINKCREATE 58
#define CULINKADDDATA 59
#define CULINKADDFILE 60
#define CULINKCOMPLETE 61
#define CULINKDESTROY 62
#define CUMODULEGETTEXREF 63
#define CUMODULEGETSURFREF 64
#define CULIBRARYLOADDATA 65
#define CULIBRARYLOADFROMFILE 66
#define CULIBRARYUNLOAD 67
#define CULIBRARYGETKERNEL 68
#define CULIBRARYGETMODULE 69
#define CUKERNELGETFUNCTION 70
#define CULIBRARYGETGLOBAL 71
#define CULIBRARYGETMANAGED 72
#define CULIBRARYGETUNIFIEDFUNCTION 73
#define CUKERNELGETATTRIBUTE 74
#define CUKERNELSETATTRIBUTE 75
#define CUKERNELSETCACHECONFIG 76
#define CUMEMGETINFO 77
#define CUMEMALLOC 78
#define CUMEMALLOCPITCH 79
#define CUMEMFREE 80
#define CUMEMGETADDRESSRANGE 81
#define CUMEMALLOCHOST 82
#define CUMEMFREEHOST 83
#define CUMEMHOSTALLOC 84
#define CUMEMHOSTGETDEVICEPOINTER 85
#define CUMEMHOSTGETFLAGS 86
#define CUMEMALLOCMANAGED 87
#define CUDEVICEGETBYPCIBUSID 88
#define CUDEVICEGETPCIBUSID 89
#define CUIPCGETEVENTHANDLE 90
#define CUIPCOPENEVENTHANDLE 91
#define CUIPCGETMEMHANDLE 92
#define CUIPCOPENMEMHANDLE 93
#define CUIPCCLOSEMEMHANDLE 94
#define CUMEMHOSTREGISTER 95
#define CUMEMHOSTUNREGISTER 96
#define CUMEMCPY 97
#define CUMEMCPYPEER 98
#define CUMEMCPYHTOD 99
#define CUMEMCPYDTOH 100
#define CUMEMCPYDTOD 101
#define CUMEMCPYDTOA 102
#define CUMEMCPYATOD 103
#define CUMEMCPYHTOA 104
#define CUMEMCPYATOH 105
#define CUMEMCPYATOA 106
#define CUMEMCPY2D 107
#define CUMEMCPY2DUNALIGNED 108
#define CUMEMCPY3D 109
#define CUMEMCPY3DPEER 110
#define CUMEMCPYASYNC 111
#define CUMEMCPYPEERASYNC 112
#define CUMEMCPYHTODASYNC 113
#define CUMEMCPYDTOHASYNC 114
#define CUMEMCPYDTODASYNC 115
#define CUMEMCPYHTOAASYNC 116
#define CUMEMCPYATOHASYNC 117
#define CUMEMCPY2DASYNC 118
#define CUMEMCPY3DASYNC 119
#define CUMEMCPY3DPEERASYNC 120
#define CUMEMSETD8 121
#define CUMEMSETD16 122
#define CUMEMSETD32 123
#define CUMEMSETD2D8 124
#define CUMEMSETD2D16 125
#define CUMEMSETD2D32 126
#define CUMEMSETD8ASYNC 127
#define CUMEMSETD16ASYNC 128
#define CUMEMSETD32ASYNC 129
#define CUMEMSETD2D8ASYNC 130
#define CUMEMSETD2D16ASYNC 131
#define CUMEMSETD2D32ASYNC 132
#define CUARRAYCREATE 133
#define CUARRAYGETDESCRIPTOR 134
#define CUARRAYGETSPARSEPROPERTIES 135
#define CUMIPMAPPEDARRAYGETSPARSEPROPERTIES 136
#define CUARRAYGETMEMORYREQUIREMENTS 137
#define CUMIPMAPPEDARRAYGETMEMORYREQUIREMENTS 138
#define CUARRAYGETPLANE 139
#define CUARRAYDESTROY 140
#define CUARRAY3DCREATE 141
#define CUARRAY3DGETDESCRIPTOR 142
#define CUMIPMAPPEDARRAYCREATE 143
#define CUMIPMAPPEDARRAYGETLEVEL 144
#define CUMIPMAPPEDARRAYDESTROY 145
#define CUMEMGETHANDLEFORADDRESSRANGE 146
#define CUMEMADDRESSRESERVE 147
#define CUMEMADDRESSFREE 148
#define CUMEMCREATE 149
#define CUMEMRELEASE 150
#define CUMEMMAP 151
#define CUMEMMAPARRAYASYNC 152
#define CUMEMUNMAP 153
#define CUMEMSETACCESS 154
#define CUMEMGETACCESS 155
#define CUMEMEXPORTTOSHAREABLEHANDLE 156
#define CUMEMIMPORTFROMSHAREABLEHANDLE 157
#define CUMEMGETALLOCATIONGRANULARITY 158
#define CUMEMGETALLOCATIONPROPERTIESFROMHANDLE 159
#define CUMEMRETAINALLOCATIONHANDLE 160
#define CUMEMFREEASYNC 161
#define CUMEMALLOCASYNC 162
#define CUMEMPOOLTRIMTO 163
#define CUMEMPOOLSETATTRIBUTE 164
#define CUMEMPOOLGETATTRIBUTE 165
#define CUMEMPOOLSETACCESS 166
#define CUMEMPOOLGETACCESS 167
#define CUMEMPOOLCREATE 168
#define CUMEMPOOLDESTROY 169
#define CUMEMALLOCFROMPOOLASYNC 170
#define CUMEMPOOLEXPORTTOSHAREABLEHANDLE 171
#define CUMEMPOOLIMPORTFROMSHAREABLEHANDLE 172
#define CUMEMPOOLEXPORTPOINTER 173
#define CUMEMPOOLIMPORTPOINTER 174
#define CUMULTICASTCREATE 175
#define CUMULTICASTADDDEVICE 176
#define CUMULTICASTBINDMEM 177
#define CUMULTICASTBINDADDR 178
#define CUMULTICASTUNBIND 179
#define CUMULTICASTGETGRANULARITY 180
#define CUPOINTERGETATTRIBUTE 181
#define CUMEMPREFETCHASYNC 182
#define CUMEMADVISE 183
#define CUMEMRANGEGETATTRIBUTE 184
#define CUMEMRANGEGETATTRIBUTES 185
#define CUPOINTERSETATTRIBUTE 186
#define CUPOINTERGETATTRIBUTES 187
#define CUSTREAMCREATE 188
#define CUSTREAMCREATEWITHPRIORITY 189
#define CUSTREAMGETPRIORITY 190
#define CUSTREAMGETFLAGS 191
#define CUSTREAMGETID 192
#define CUSTREAMGETCTX 193
#define CUSTREAMWAITEVENT 194
#define CUSTREAMADDCALLBACK 195
#define CUSTREAMBEGINCAPTURE 196
#define CUTHREADEXCHANGESTREAMCAPTUREMODE 197
#define CUSTREAMENDCAPTURE 198
#define CUSTREAMISCAPTURING 199
#define CUSTREAMGETCAPTUREINFO 200
#define CUSTREAMUPDATECAPTUREDEPENDENCIES 201
#define CUSTREAMATTACHMEMASYNC 202
#define CUSTREAMQUERY 203
#define CUSTREAMSYNCHRONIZE 204
#define CUSTREAMDESTROY 205
#define CUSTREAMCOPYATTRIBUTES 206
#define CUSTREAMGETATTRIBUTE 207
#define CUSTREAMSETATTRIBUTE 208
#define CUEVENTCREATE 209
#define CUEVENTRECORD 210
#define CUEVENTRECORDWITHFLAGS 211
#define CUEVENTQUERY 212
#define CUEVENTSYNCHRONIZE 213
#define CUEVENTDESTROY 214
#define CUEVENTELAPSEDTIME 215
#define CUIMPORTEXTERNALMEMORY 216
#define CUEXTERNALMEMORYGETMAPPEDBUFFER 217
#define CUEXTERNALMEMORYGETMAPPEDMIPMAPPEDARRAY 218
#define CUDESTROYEXTERNALMEMORY 219
#define CUIMPORTEXTERNALSEMAPHORE 220
#define CUSIGNALEXTERNALSEMAPHORESASYNC 221
#define CUWAITEXTERNALSEMAPHORESASYNC 222
#define CUDESTROYEXTERNALSEMAPHORE 223
#define CUSTREAMWAITVALUE32 224
#define CUSTREAMWAITVALUE64 225
#define CUSTREAMWRITEVALUE32 226
#define CUSTREAMWRITEVALUE64 227
#define CUSTREAMBATCHMEMOP 228
#define CUFUNCGETATTRIBUTE 229
#define CUFUNCSETATTRIBUTE 230
#define CUFUNCSETCACHECONFIG 231
#define CUFUNCSETSHAREDMEMCONFIG 232
#define CUFUNCGETMODULE 233
#define CULAUNCHKERNEL 234
#define CULAUNCHKERNELEX 235
#define CULAUNCHCOOPERATIVEKERNEL 236
#define CULAUNCHCOOPERATIVEKERNELMULTIDEVICE 237
#define CULAUNCHHOSTFUNC 238
#define CUFUNCSETBLOCKSHAPE 239
#define CUFUNCSETSHAREDSIZE 240
#define CUPARAMSETSIZE 241
#define CUPARAMSETI 242
#define CUPARAMSETF 243
#define CUPARAMSETV 244
#define CULAUNCH 245
#define CULAUNCHGRID 246
#define CULAUNCHGRIDASYNC 247
#define CUPARAMSETTEXREF 248
#define CUGRAPHCREATE 249
#define CUGRAPHADDKERNELNODE 250
#define CUGRAPHKERNELNODEGETPARAMS 251
#define CUGRAPHKERNELNODESETPARAMS 252
#define CUGRAPHADDMEMCPYNODE 253
#define CUGRAPHMEMCPYNODEGETPARAMS 254
#define CUGRAPHMEMCPYNODESETPARAMS 255
#define CUGRAPHADDMEMSETNODE 256
#define CUGRAPHMEMSETNODEGETPARAMS 257
#define CUGRAPHMEMSETNODESETPARAMS 258
#define CUGRAPHADDHOSTNODE 259
#define CUGRAPHHOSTNODEGETPARAMS 260
#define CUGRAPHHOSTNODESETPARAMS 261
#define CUGRAPHADDCHILDGRAPHNODE 262
#define CUGRAPHCHILDGRAPHNODEGETGRAPH 263
#define CUGRAPHADDEMPTYNODE 264
#define CUGRAPHADDEVENTRECORDNODE 265
#define CUGRAPHEVENTRECORDNODEGETEVENT 266
#define CUGRAPHEVENTRECORDNODESETEVENT 267
#define CUGRAPHADDEVENTWAITNODE 268
#define CUGRAPHEVENTWAITNODEGETEVENT 269
#define CUGRAPHEVENTWAITNODESETEVENT 270
#define CUGRAPHADDEXTERNALSEMAPHORESSIGNALNODE 271
#define CUGRAPHEXTERNALSEMAPHORESSIGNALNODEGETPARAMS 272
#define CUGRAPHEXTERNALSEMAPHORESSIGNALNODESETPARAMS 273
#define CUGRAPHADDEXTERNALSEMAPHORESWAITNODE 274
#define CUGRAPHEXTERNALSEMAPHORESWAITNODEGETPARAMS 275
#define CUGRAPHEXTERNALSEMAPHORESWAITNODESETPARAMS 276
#define CUGRAPHADDBATCHMEMOPNODE 277
#define CUGRAPHBATCHMEMOPNODEGETPARAMS 278
#define CUGRAPHBATCHMEMOPNODESETPARAMS 279
#define CUGRAPHEXECBATCHMEMOPNODESETPARAMS 280
#define CUGRAPHADDMEMALLOCNODE 281
#define CUGRAPHMEMALLOCNODEGETPARAMS 282
#define CUGRAPHADDMEMFREENODE 283
#define CUGRAPHMEMFREENODEGETPARAMS 284
#define CUDEVICEGRAPHMEMTRIM 285
#define CUDEVICEGETGRAPHMEMATTRIBUTE 286
#define CUDEVICESETGRAPHMEMATTRIBUTE 287
#define CUGRAPHCLONE 288
#define CUGRAPHNODEFINDINCLONE 289
#define CUGRAPHNODEGETTYPE 290
#define CUGRAPHGETNODES 291
#define CUGRAPHGETROOTNODES 292
#define CUGRAPHGETEDGES 293
#define CUGRAPHNODEGETDEPENDENCIES 294
#define CUGRAPHNODEGETDEPENDENTNODES 295
#define CUGRAPHADDDEPENDENCIES 296
#define CUGRAPHREMOVEDEPENDENCIES 297
#define CUGRAPHDESTROYNODE 298
#define CUGRAPHINSTANTIATE 299
#define CUGRAPHINSTANTIATEWITHPARAMS 300
#define CUGRAPHEXECGETFLAGS 301
#define CUGRAPHEXECKERNELNODESETPARAMS 302
#define CUGRAPHEXECMEMCPYNODESETPARAMS 303
#define CUGRAPHEXECMEMSETNODESETPARAMS 304
#define CUGRAPHEXECHOSTNODESETPARAMS 305
#define CUGRAPHEXECCHILDGRAPHNODESETPARAMS 306
#define CUGRAPHEXECEVENTRECORDNODESETEVENT 307
#define CUGRAPHEXECEVENTWAITNODESETEVENT 308
#define CUGRAPHEXECEXTERNALSEMAPHORESSIGNALNODESETPARAMS 309
#define CUGRAPHEXECEXTERNALSEMAPHORESWAITNODESETPARAMS 310
#define CUGRAPHNODESETENABLED 311
#define CUGRAPHNODEGETENABLED 312
#define CUGRAPHUPLOAD 313
#define CUGRAPHLAUNCH 314
#define CUGRAPHEXECDESTROY 315
#define CUGRAPHDESTROY 316
#define CUGRAPHEXECUPDATE 317
#define CUGRAPHKERNELNODECOPYATTRIBUTES 318
#define CUGRAPHKERNELNODEGETATTRIBUTE 319
#define CUGRAPHKERNELNODESETATTRIBUTE 320
#define CUGRAPHDEBUGDOTPRINT 321
#define CUUSEROBJECTCREATE 322
#define CUUSEROBJECTRETAIN 323
#define CUUSEROBJECTRELEASE 324
#define CUGRAPHRETAINUSEROBJECT 325
#define CUGRAPHRELEASEUSEROBJECT 326
#define CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSOR 327
#define CUOCCUPANCYMAXACTIVEBLOCKSPERMULTIPROCESSORWITHFLAGS 328
#define CUOCCUPANCYMAXPOTENTIALBLOCKSIZE 329
#define CUOCCUPANCYMAXPOTENTIALBLOCKSIZEWITHFLAGS 330
#define CUOCCUPANCYAVAILABLEDYNAMICSMEMPERBLOCK 331
#define CUOCCUPANCYMAXPOTENTIALCLUSTERSIZE 332
#define CUOCCUPANCYMAXACTIVECLUSTERS 333
#define CUTEXREFSETARRAY 334
#define CUTEXREFSETMIPMAPPEDARRAY 335
#define CUTEXREFSETADDRESS 336
#define CUTEXREFSETADDRESS2D 337
#define CUTEXREFSETFORMAT 338
#define CUTEXREFSETADDRESSMODE 339
#define CUTEXREFSETFILTERMODE 340
#define CUTEXREFSETMIPMAPFILTERMODE 341
#define CUTEXREFSETMIPMAPLEVELBIAS 342
#define CUTEXREFSETMIPMAPLEVELCLAMP 343
#define CUTEXREFSETMAXANISOTROPY 344
#define CUTEXREFSETBORDERCOLOR 345
#define CUTEXREFSETFLAGS 346
#define CUTEXREFGETADDRESS 347
#define CUTEXREFGETARRAY 348
#define CUTEXREFGETMIPMAPPEDARRAY 349
#define CUTEXREFGETADDRESSMODE 350
#define CUTEXREFGETFILTERMODE 351
#define CUTEXREFGETFORMAT 352
#define CUTEXREFGETMIPMAPFILTERMODE 353
#define CUTEXREFGETMIPMAPLEVELBIAS 354
#define CUTEXREFGETMIPMAPLEVELCLAMP 355
#define CUTEXREFGETMAXANISOTROPY 356
#define CUTEXREFGETBORDERCOLOR 357
#define CUTEXREFGETFLAGS 358
#define CUTEXREFCREATE 359
#define CUTEXREFDESTROY 360
#define CUSURFREFSETARRAY 361
#define CUSURFREFGETARRAY 362
#define CUTEXOBJECTCREATE 363
#define CUTEXOBJECTDESTROY 364
#define CUTEXOBJECTGETRESOURCEDESC 365
#define CUTEXOBJECTGETTEXTUREDESC 366
#define CUTEXOBJECTGETRESOURCEVIEWDESC 367
#define CUSURFOBJECTCREATE 368
#define CUSURFOBJECTDESTROY 369
#define CUSURFOBJECTGETRESOURCEDESC 370
#define CUTENSORMAPENCODETILED 371
#define CUTENSORMAPENCODEIM2COL 372
#define CUTENSORMAPREPLACEADDRESS 373
#define CUDEVICECANACCESSPEER 374
#define CUCTXENABLEPEERACCESS 375
#define CUCTXDISABLEPEERACCESS 376
#define CUDEVICEGETP2PATTRIBUTE 377
#define CUGRAPHICSUNREGISTERRESOURCE 378
#define CUGRAPHICSSUBRESOURCEGETMAPPEDARRAY 379
#define CUGRAPHICSRESOURCEGETMAPPEDMIPMAPPEDARRAY 380
#define CUGRAPHICSRESOURCEGETMAPPEDPOINTER 381
#define CUGRAPHICSRESOURCESETMAPFLAGS 382
#define CUGRAPHICSMAPRESOURCES 383
#define CUGRAPHICSUNMAPRESOURCES 384
#define CUGETPROCADDRESS 385
#define CUCOREDUMPGETATTRIBUTE 386
#define CUCOREDUMPGETATTRIBUTEGLOBAL 387
#define CUCOREDUMPSETATTRIBUTE 388
#define CUCOREDUMPSETATTRIBUTEGLOBAL 389
#define CUGETEXPORTTABLE 390
