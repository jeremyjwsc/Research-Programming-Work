Imports System.Data.SqlClient
Partial Class Records
    Inherits System.Web.UI.Page
    Dim fn As New clsFunctions
    Dim errDes As String = ""
    Private Sub frmMain_Load(sender As Object, e As EventArgs) Handles frmMain.Load
        lbStatus.Text = ""
        If Not IsPostBack = True Then
            txtSelect.Text = 10
            txtID.Text = ""
            GetRecordsData()
        End If
    End Sub
    Private Sub GetRecordsData()

        Dim IsHeader As Boolean = True
        Dim sqlStr As String = ""
        If Val(txtSelect.Text) = 0 Then
            sqlStr = " SELECT * FROM [dbo].[Records]"
        Else
            sqlStr = " SELECT TOP " & txtSelect.Text & " * FROM [dbo].[Records]"
        End If
        If Val(txtID.Text) > 0 Then
            sqlStr = sqlStr & " WHERE [ID] IN (" & txtID.Text & ")"
        End If
        sqlStr = sqlStr & " ORDER BY [ID] DESC"
        Dim Reader As SqlDataReader = fn.SqlDataRead(sqlStr, errDes)
        If Reader Is Nothing Then
            lbStatus.Text = errDes
            Exit Sub
        End If
        If Reader.HasRows = False Then Exit Sub
        Dim IsColorA As Boolean = False
        pnlTimeline.Controls.Clear()
        While Reader.Read()
            Dim pnl As New Panel
            Dim lb As New Label
            Dim br As New LiteralControl("<br/>")
            pnl.Controls.Add(br)
            If IsHeader = True Then
                lb.Text = "ID"
            Else
                lb.Text = Reader("ID").ToString
            End If
            lb.Font.Bold = True
            lb.Width = 80
            lb.Font.Size = 10
            lb.Style.Add("margin-right", "5px")
            lb.Style.Add("text-align", "right")
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 200
            If IsHeader = True Then
                lb.Text = "Name"
                lb.Font.Bold = True
            Else
                lb.Text = Reader("FirstName").ToString & " " & Reader("LastName").ToString
            End If
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 250
            lb.Font.Size = 10
            If IsHeader = True Then
                lb.Text = "Address"
                lb.Font.Bold = True
            Else
                lb.Text = Reader("Address").ToString
            End If
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 150
            lb.Font.Size = 10
            If IsHeader = True Then
                lb.Text = "Phone"
                lb.Font.Bold = True
            Else
                lb.Text = Reader("Phone").ToString
            End If
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 200
            lb.Font.Size = 10
            If IsHeader = True Then
                lb.Text = "Email"
                lb.Font.Bold = True
            Else
                lb.Text = Reader("Email").ToString
            End If
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 100
            lb.Font.Size = 10
            lb.Style.Add("margin-right", "10px")
            lb.Style.Add("text-align", "right")
            If IsHeader = True Then
                lb.Text = "Salary"
                lb.Font.Bold = True
            Else
                lb.Text = Format(Reader("Salary"), "0.00")
            End If
            pnl.Controls.Add(lb)
            lb = New Label
            lb.Width = 150
            lb.Font.Size = 10
            If IsHeader = True Then
                lb.Text = "Timestamp"
                lb.Font.Bold = True
            Else
                lb.Text = Reader("Timestamp").ToString
            End If
            pnl.Controls.Add(lb)
            If IsColorA = False Then
                pnl.BackColor = Drawing.Color.FromArgb(255, 215, 215, 215)
                IsColorA = True
            Else
                pnl.BackColor = Drawing.Color.FromArgb(255, 205, 205, 205)
                IsColorA = False
            End If
            pnlTimeline.Controls.Add(pnl)
            If IsHeader = True Then
                Reader = fn.SqlDataRead(sqlStr, errDes) 'start from beginning
                IsHeader = False
            End If
        End While
    End Sub

    Private Sub lnkBtnSelect_Click(sender As Object, e As EventArgs) Handles lnkBtnSelect.Click
        txtID.Text = ""
        GetRecordsData()
    End Sub

    Private Sub lnkBtnFind_Click(sender As Object, e As EventArgs) Handles lnkBtnFind.Click
        txtSelect.Text = ""
        GetRecordsData()
    End Sub
End Class
