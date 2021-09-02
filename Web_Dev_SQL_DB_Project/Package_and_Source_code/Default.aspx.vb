Imports System.Data.SqlClient
Partial Class _Default
    Inherits System.Web.UI.Page
    Dim fn As New clsFunctions
    Dim errDes As String = Nothing

    Private Sub frmMain_Load(sender As Object, e As EventArgs) Handles frmMain.Load

        lbStatus.Text = ""
        lbTimeStamp.Text = ""
        lbToRec.Text = ""
        If Not IsPostBack = True Then
            Initialization()
            TotalRecord()
            NewID()
        End If
    End Sub


    Private Sub Initialization()
        ' Creating table if not exist
        Dim sqlStr As String =
            " IF OBJECT_ID('dbo.Records') IS NULL " &
            " CREATE TABLE [Records] " &
            " ([ID] INT PRIMARY KEY," &
            " [FirstName] NVARCHAR(50)," &
            " [LastName] NVARCHAR(50)," &
            " [Address] NVARCHAR(150)," &
            " [Phone] NVARCHAR(50)," &
            " [Email] NVARCHAR(50)," &
            " [Salary] NUMERIC(18,2)," &
            " [Timestamp] DATETIME);"
        Dim Reply As Boolean = fn.SqlTransact(sqlStr, errDes)
        If Reply = False Then
            lbStatus.Text = errDes
        End If

    End Sub
    Private Sub NewID()
        Dim sqlStr As String = " SELECT MAX([ID]) AS maxID FROM [dbo].[Records]"
        Dim Reader As SqlDataReader = fn.SqlDataRead(sqlStr, errDes)
        If Reader Is Nothing Then
            lbStatus.Text = errDes
            Exit Sub
        End If
        If Reader.HasRows = False Then Exit Sub
        If Reader.Read() = True Then
            If IsDBNull(Reader("maxID")) = False Then
                txtID.Text = Reader("maxID") + 1
            Else
                txtID.Text = 1
            End If
            Reader.Close()
        End If

    End Sub
    Private Sub TotalRecord()
        Dim sqlStr As String = " SELECT COUNT([ID]) AS ToRec FROM [dbo].[Records]"
        Dim Reader As SqlDataReader = fn.SqlDataRead(sqlStr, errDes)
        If Reader Is Nothing Then
            lbStatus.Text = errDes
            Exit Sub
        End If
        If Reader.HasRows = False Then Exit Sub
        If Reader.Read() = True Then
            If IsDBNull(Reader("ToRec")) = False Then lbToRec.Text = "Total: " & Reader("ToRec").ToString & " Record(s)"
            Reader.Close()
        End If

    End Sub
    Private Sub Create()
        Dim sqlStr As String =
            " INSERT INTO [dbo].[Records] ([ID],[FirstName],[LastName],[Address],[Phone],[Email],[Salary],[Timestamp]) " &
            " VALUES (IIF((SELECT MAX(ID) FROM [dbo].[Records]) IS NULL,0,(SELECT MAX(ID) FROM [dbo].[Records]))+1,'" &
            txtFirstName.Text & "','" & txtLastName.Text & "','" & txtAddress.Text & "','" & txtPhone.Text & "','" &
            txtEmail.Text & "'," & txtSalary.Text & ",GETDATE())"
        Dim Reply As Boolean = fn.SqlTransact(sqlStr, errDes)
        If Reply = False Then
            lbStatus.Text = errDes
        Else
            txtID.Text = ""
            txtFirstName.Text = ""
            txtLastName.Text = ""
            txtAddress.Text = ""
            txtPhone.Text = ""
            txtEmail.Text = ""
            txtSalary.Text = ""
            lbTimeStamp.Text = ""
        End If
    End Sub

    Private Sub Show()
        If Val(txtID.Text) = 0 Then
            lbStatus.Text = "Please enter ID in the ID text box then click on Show!"
            Exit Sub
        End If
        Dim sqlStr As String = " SELECT * FROM [dbo].[Records] WHERE ID = " & txtID.Text
        Dim Reader As SqlDataReader = fn.SqlDataRead(sqlStr, errDes)
        If Reader Is Nothing Then
            lbStatus.Text = errDes
        Else
            If Reader.HasRows = False Then
                lbStatus.Text = "No record found."
                txtID.Text = ""
                txtFirstName.Text = ""
                txtLastName.Text = ""
                txtAddress.Text = ""
                txtPhone.Text = ""
                txtEmail.Text = ""
                txtSalary.Text = ""
                lbTimeStamp.Text = ""
                Exit Sub
            End If
            Reader.Read()
            txtID.Text = Reader("ID").ToString
            txtFirstName.Text = Reader("FirstName").ToString
            txtLastName.Text = Reader("LastName").ToString
            txtAddress.Text = Reader("Address").ToString
            txtPhone.Text = Reader("Phone").ToString
            txtEmail.Text = Reader("Email").ToString
            txtSalary.Text = Reader("Salary").ToString
            lbTimeStamp.Text = Reader("Timestamp").ToString
        End If
    End Sub

    Private Sub Update()
        Dim sqlStr As String =
            " UPDATE [dbo].[Records] SET " &
            " [FirstName] = '" & txtFirstName.Text & "'," &
            " [LastName] = '" & txtLastName.Text & "'," &
            " [Address] = '" & txtAddress.Text & "'," &
            " [Phone] = '" & txtPhone.Text & "'," &
            " [Email] = '" & txtEmail.Text & "'," &
            " [Salary] = " & txtSalary.Text &
            " WHERE [ID] = " & txtID.Text
        Dim Reply As Boolean = fn.SqlTransact(sqlStr, errDes)
        If Reply = False Then
            lbStatus.Text = errDes
        Else
            txtID.Text = ""
            txtFirstName.Text = ""
            txtLastName.Text = ""
            txtAddress.Text = ""
            txtPhone.Text = ""
            txtEmail.Text = ""
            txtSalary.Text = ""
            lbTimeStamp.Text = ""
        End If
    End Sub

    Private Sub Delete()
        Dim sqlStr As String = " DELETE  FROM [dbo].[Records] WHERE [ID] = " & txtID.Text
        Dim Reply As Boolean = fn.SqlTransact(sqlStr, errDes)
        If Reply = False Then
            lbStatus.Text = errDes
        Else
            txtID.Text = ""
            txtFirstName.Text = ""
            txtLastName.Text = ""
            txtAddress.Text = ""
            txtPhone.Text = ""
            txtEmail.Text = ""
            txtSalary.Text = ""
            lbTimeStamp.Text = ""
        End If
    End Sub



    Private Sub lnkBtnCreate_Click(sender As Object, e As EventArgs) Handles lnkBtnCreate.Click
        Create()
        TotalRecord()
        NewID()
    End Sub

    Private Sub lnkBtnShow_Click(sender As Object, e As EventArgs) Handles lnkBtnShow.Click
        Show()
        TotalRecord()
    End Sub

    Private Sub lnkBtnUpdate_Click(sender As Object, e As EventArgs) Handles lnkBtnUpdate.Click
        Update()
        TotalRecord()
        NewID()
    End Sub

    Private Sub lnkBtnDelete_Click(sender As Object, e As EventArgs) Handles lnkBtnDelete.Click
        Delete()
        TotalRecord()
        NewID()
    End Sub
End Class
