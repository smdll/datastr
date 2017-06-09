# -*- coding: utf-8 -*-
import sys
from wx import *

INF = 100

Edge = [
	[0,   5,   INF, 5,   10,  INF, INF, INF, INF, INF],
	[5,   0,   2,   3,   INF, INF, INF, INF, INF, INF],
	[INF, 2,   0,   INF, INF, INF, INF, 4,   3,   INF],
	[5,   3,   INF, 0,   5,   10,  INF, INF, INF, INF],
	[10,  INF, INF, 5,   0,   INF, INF, INF, INF, INF],
	[INF, INF, INF, 10,  INF, 0,   8,   15,  INF, INF],
	[INF, INF, INF, INF, INF, 8,   0,   INF, INF, INF],
	[INF, INF, 4,   INF, INF, 15,  INF, 0,   3,   4],
	[INF, INF, 3,   INF, INF, INF, INF, 3,   0,   INF],
	[INF, INF, INF, INF, INF, INF, INF, 4,   INF, 0]]

dist = [[0 for i in range(10)] for i in range(10)]
path = [[0 for i in range(10)] for i in range(10)]

class edge():
	name = ""
	info = ""
map = [edge() for i in range(10)]
map[0].name = "南门"
map[0].info = "广西大学主进出口"
map[1].name = "西苑餐厅"
map[1].info = "南校园的餐厅之一"
map[2].name = "图书馆"
map[2].info = "广西大学图书馆"
map[3].name = "西体育馆"
map[3].info = "西校园体育馆"
map[4].name = "西门"
map[4].info = "西校园进出口"
map[5].name = "农场"
map[5].info = "农类生产实验基地"
map[6].name = "行健学院"
map[6].info = "广西大学行健学院"
map[7].name = "东水塔"
map[7].info = "东校园地标"
map[8].name = "校医院"
map[8].info = "广西大学校医院"
map[9].name = "东门"
map[9].info = "东校园进出口"

class MainFrame(wx.Frame):
	def __init__(self, parent):
		super(MainFrame, self).__init__(parent, title = "广西大学导游系统", size = (260, 350), style = wx.DEFAULT_FRAME_STYLE & ~(wx.RESIZE_BORDER | wx.MAXIMIZE_BOX))
		self.initUI()
		self.floyd()
	
	def initUI(self):
		self.List = TextCtrl(self, pos = (0, 0), size = (260, 100), name = "&List", style = wx.TE_MULTILINE|wx.TE_READONLY)
		for i in range(0, 8, 2):
			self.List.AppendText("%d:%s\t\t"%(i + 1, map[i].name))
			self.List.AppendText("%d:%s\n"%(i + 2, map[i + 1].name))
		self.List.AppendText("%d:%s\t\t"%(i + 3, map[i + 2].name))
		self.List.AppendText("%d:%s"%(i + 4, map[i + 3].name))
		self.Lb1 = StaticText(self, label = "查询景点：", pos = (0, 110), size = (75, 20), name = "&Label1")
		self.Ent1 = TextCtrl(self, pos = (75, 110), size = (75, 20), name = "&Text1")
		self.Bt1 = Button(self, id = 100, label = "查询！", pos = (150, 105), size = (50, 30), name = "&Check1")
		self.Lb2 = StaticText(self, label = "查询路径：", pos = (0, 135), size = (75, 40), name = "&Label2")
		self.Lb3 = StaticText(self, label = "从：", pos = (0, 160), size = (30, 40), name = "&Label3")
		self.Ent2 = TextCtrl(self, pos = (30, 160), size = (75, 20), name = "&Text2")
		self.Lb4 = StaticText(self, label = "到：", pos = (105, 160), size = (30, 20), name = "&Label4")
		self.Ent3 = TextCtrl(self, pos = (135, 160), size = (75, 20), name = "&Text3")
		self.Bt2 = Button(self, id = 101, label = "查询！", pos = (210, 155), size = (50, 30), name = "&Check2")
		self.Text = TextCtrl(self, pos = (0, 190), size = (260, 150), name = "&Text", style = wx.TE_MULTILINE|wx.TE_READONLY)
		self.Show(True)
		self.Bind(wx.EVT_BUTTON, self.printNode, self.Bt1)
		self.Bind(wx.EVT_BUTTON, self.printPath, self.Bt2)

	def floyd(self):
		for i in range(10):
			for j in range(10):
				dist[i][j] = Edge[i][j]
				if Edge[i][j] == INF:
						path[i][j] = -1
				else:
					path[i][j] = i
		for k in range(10):
			for i in range(10):
				for j in range(10):
					if dist[i][k] != INF and dist[k][j] != INF and dist[i][j] > dist[i][k] + dist[k][j]:
						dist[i][j] = dist[i][k] + dist[k][j]
						path[i][j] = path[k][j]

	def printNode(self, event):
		try:
			i = int(self.Ent1.GetValue()) - 1
		except ValueError:
			wx.MessageBox("输入只能为数字", "非法输入", wx.OK, self)
			return
		if i > 9 or i < 0:
			wx.MessageBox("输入超过限制", "非法输入", wx.OK, self)
			return
		wx.MessageBox("%s：%s"%(map[i].name, map[i].info), "结果", wx.OK, self)

	def printPath(self, event):
		try:
			i = int(self.Ent2.GetValue()) - 1
			j = int(self.Ent3.GetValue()) - 1
		except ValueError:
			wx.MessageBox("输入只能为数字", "非法输入", wx.OK, self)
			return
		if i > 9 or i < 0 or j > 9 or j < 0:
			wx.MessageBox("输入超过限制", "非法输入", wx.OK, self)
			return
		apath = [0 for o in range(0, 10)]
		res = "从 %s 到 %s 的路径：\n"%(map[i].name, map[j].name)
		k = path[i][j]
		d = 0
		apath[d] = j
		while k != -1 and k != i:
			d = d + 1
			apath[d] = k
			k = path[i][k]
		d = d + 1
		apath[d] = i
		res = "%s%s"%(res, map[apath[d]].name)		
		for s in range(d - 1, -1, -1):
			res = "%s -> %s"%(res, map[apath[s]].name)
		res = "%s\n路径长度：%s米"%(res, dist[i][j] * 100)
		self.Text.SetValue(res)

if __name__ == "__main__":
	root = wx.App()
	MainFrame(None)
	root.MainLoop()
