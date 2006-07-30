<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">

  <msxsl:script language="JScript" implements-prefix="dedek">
    function hex(cislo) {
      return cislo.toString(16);
    }
  </msxsl:script>



<xsl:template match="/active_list">		
		

  	<xsl:element name="dialog_data">
		
			<xsl:apply-templates select="hyp_4ft[position()=1]" mode="attributes"/>
		
			<xsl:element name="values">
				<xsl:apply-templates select="hyp_4ft" mode="values"/>
			</xsl:element>
		
  	</xsl:element>
  
</xsl:template>

	
	



	<!-- vypise atributy -->
<xsl:template match="node()" mode="attributes">		
		
		
	<xsl:element name="attributes">

		<xsl:apply-templates select="@*" mode="attributes"/>

	</xsl:element>

</xsl:template>
	


	<!-- vypise vsechny atributy -->
<xsl:template match="@*" mode="attributes">

	<xsl:element name="attribute">
		
		<xsl:attribute name="name"><xsl:value-of select="name()"/></xsl:attribute>
		
	</xsl:element>

    <xsl:apply-templates select="@*"/>
    
</xsl:template>






	<!-- vypise hodnoty -->
<xsl:template match="node()" mode="values">		
		
		<xsl:element name="value">
			<xsl:apply-templates select="@*" mode="values"/>
		</xsl:element>

</xsl:template>





	<!-- naplni hodnoty atributu krome cedentu-->
<xsl:template match="@*" mode="values">
	<xsl:attribute name="{name()}"><xsl:value-of select="."/></xsl:attribute>
</xsl:template>



    	
	
	<!-- naplni hodnotu cedentu-->
<xsl:template match="@antecedent | @succedent | @condition" mode="values">
	
	
	<xsl:attribute name="{name()}">
    	<xsl:apply-templates select="id(.)" mode="values"/>
	</xsl:attribute>
		

    <xsl:apply-templates select="@*"/>
    
</xsl:template>



	

	<!-- literaly -> cedent -->
<xsl:template match="ti_cedent" mode="values">		
    	<xsl:apply-templates select="ti_literal" mode="values"/>
</xsl:template>
	




	<!-- preformatuje literal -->
<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
</xsl:template>
	






</xsl:stylesheet>
