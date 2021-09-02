<%@ Page Language="VB" AutoEventWireup="false" CodeFile="Default.aspx.vb" Inherits="_Default" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style>
        .lnkBtn{
            margin:5px 5px 5px 5px;
            display:inline;
       
        }
    </style>
</head>
<body>
        <div style="width:700px;margin:auto;text-align:left;border-radius:10px;border-width:2px;border-style:solid;
         border-color:rgb(175,175,255);background-color:rgb(215,215,255);font-family:sans-serif;">
        <form id="frmMain" runat="server" style="padding:10px 10px 10px 10px">
            <asp:ScriptManager ID="sm" runat="server"></asp:ScriptManager>
            <asp:UpdateProgress ID="upMain" runat="server">
                <ProgressTemplate>
                    <p>Processing...</p>
                </ProgressTemplate>
            </asp:UpdateProgress>
            <asp:UpdatePanel ID="updName" runat="server">
                <ContentTemplate>
                    <div style="text-align:right;">
                        <asp:Label ID="lbStatus" runat="server" ForeColor="Red" Text="#Status#"></asp:Label>
                    </div>
                    <label for="txtID" style="display:block;cursor:pointer;">ID:</label>
                    <asp:TextBox ID="txtID" runat="server" Width="150px" TextMode="Number"></asp:TextBox>
                    <label for="txtFirstName" style="display:block;cursor:pointer; margin-top:10px;">First Name:</label>
                    <asp:TextBox ID="txtFirstName" runat="server" Width="300px"></asp:TextBox>
                    <label for="txtLastName" style="display:block;cursor:pointer;margin-top:10px;">Last Name:</label>
                    <asp:TextBox ID="txtLastName" runat="server" Width="300px"></asp:TextBox>
                    <label for="txtAddress" style="display:block;cursor:pointer;margin-top:10px;">Address:</label>
                    <asp:TextBox ID="txtAddress" runat="server" Width="600px"></asp:TextBox>
                    <label for="txtPhone" style="display:block;cursor:pointer;margin-top:10px;">Phone:</label>
                    <asp:TextBox ID="txtPhone" runat="server" Width="300px" TextMode="Phone"></asp:TextBox>
                    <label for="txtEmail" style="display:block;cursor:pointer;margin-top:10px;">Email:</label>
                    <asp:TextBox ID="txtEmail" runat="server" Width="300px" TextMode="Email"></asp:TextBox>
                    <label for="txtSalary" style="display:block;cursor:pointer;margin-top:10px;">Salary:</label>
                    <asp:TextBox ID="txtSalary" runat="server" Width="300px" TextMode="Number"></asp:TextBox>
                    <asp:Label ID="lbTimeStamp" runat="server" Text="#Timestamp#" 
                                    style="display:block;margin-top:10px;"></asp:Label>
                  <div style="text-align:left;">
                      <asp:Label ID="lbToRec" runat="server" Text="#Total Record#" style="display:block;margin-top:10px;"></asp:Label>
                  </div>
                    <div style="margin-top:20px;">
                        <table style="width:650px;margin:auto;">
                            <tr>
                                <td style="text-align:left;">
                                    <asp:HyperLink ID="hpLnkRecords" runat="server" CssClass="lnkBtn" NavigateUrl="~/Records.aspx">Records</asp:HyperLink>
                                    <asp:HyperLink ID="hpLnkAverage" runat="server" CssClass="lnkBtn" NavigateUrl="~/Average.aspx">Average</asp:HyperLink>
                                </td>
                                <td style="text-align:right;">
                                    <asp:LinkButton ID="lnkBtnCreate" runat="server" CssClass="lnkBtn">Create</asp:LinkButton>
                                    <asp:LinkButton ID="lnkBtnShow" runat="server" CssClass="lnkBtn">Show</asp:LinkButton>
                                    <asp:LinkButton ID="lnkBtnUpdate" runat="server" CssClass="lnkBtn">Update</asp:LinkButton>
                                    <asp:LinkButton ID="lnkBtnDelete" runat="server" CssClass="lnkBtn">Delete</asp:LinkButton>
                                </td>
                            </tr>
                        </table>
                    </div>
                  
                </ContentTemplate>
            
            </asp:UpdatePanel>
       </form>
    </div>
</body>
</html>
