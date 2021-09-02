<%@ Page Language="VB" AutoEventWireup="false" CodeFile="Records.aspx.vb" Inherits="Records" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
        <style>
        .lnkBtn{
            margin:5px 5px 5px 5px;
            display:inline;
       
        }
        .txtCenter{
            text-align:center;
        }
    </style>
</head>
<body>
        <div style="width:1250px;margin:auto;text-align:left;border-radius:10px;border-width:2px;border-style:solid;
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
                   <div style="text-align:right;">
                       <asp:HyperLink ID="hpLnkHome" runat="server" CssClass="lnkBtn" NavigateUrl="~/Default.aspx">Home</asp:HyperLink>
                       <asp:HyperLink ID= "hpLnkAverage" runat="server" CssClass="lnkBtn" NavigateUrl="~/Average.aspx">Average</asp:HyperLink>
                    </div>
                    <div style="margin-top:10px;">
                        <table style="width:100%; margin:auto;">
                            <tr>
                                <td style="text-align:left;">
                                    <label for="txtID" style="display:block;cursor:pointer;">ID:</label>
                                    <asp:TextBox ID="txtID" runat="server" Width="100px" TextMode="Number" CssClass="txtCenter"></asp:TextBox>
                                    <asp:LinkButton ID="lnkBtnFind" runat="server" CssClass="lnkBtn">Find</asp:LinkButton>
                                </td>
                                <td style="text-align:right;">
                                    <label for="txtSelect" style="display:block;cursor:pointer;padding-right:75px;">Select Rows:</label>
                                    <asp:TextBox ID="txtSelect" runat="server" Width="100px" TextMode="Number" CssClass="txtCenter"></asp:TextBox>
                                    <asp:LinkButton ID="lnkBtnSelect" runat="server" CssClass="lnkBtn">Select</asp:LinkButton>
                                </td>
                            </tr>
                        </table>
                    </div>
                    <div style="text-align:left; margin-top:10px;background-color: rgb(200,200,200);">
                        <p style="background-color: rgb(192,192,192);padding:3px 3px 3px 3px; font-weight:bold;text-align:center;">Records</p>
                        <asp:Panel ID="pnlTimeline" runat="server" Font-Size="Small">
                            <%-- Timeline data will add here --%>
                        </asp:Panel>

                    </div>
                </ContentTemplate>
            
            </asp:UpdatePanel>
       </form>
    </div>
</body>
</html>
