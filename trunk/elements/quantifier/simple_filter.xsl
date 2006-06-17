<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      xmlns:msxsl="urn:schemas-microsoft-com:xslt"
      xmlns:dedek="http://reportasistent.com/dedek_namespace"
      version="1.0">



  <xsl:template match="/active_list">		
		<xsl:text disable-output-escaping="yes">

&lt;dialog_data&gt;
		</xsl:text>				

		<xsl:apply-templates select="quantifier[position()=1]" mode="attributes"/>





		<xsl:text disable-output-escaping="yes">
	&lt;values&gt;</xsl:text>				
	

		<xsl:apply-templates select="quantifier" mode="values"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/values&gt;
		</xsl:text>				




		<xsl:text disable-output-escaping="yes">
&lt;/dialog_data&gt;
		</xsl:text>				
	</xsl:template>

	
	



	<!-- vypise atributy -->
	<xsl:template match="node()" mode="attributes">		
		
		<xsl:text disable-output-escaping="yes">
	&lt;attributes&gt;</xsl:text>				

		<xsl:apply-templates select="@*" mode="attributes"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/attributes&gt;
		</xsl:text>				

	</xsl:template>
	


	<!-- vypise vsechny atributy -->
	<xsl:template match="@*" mode="attributes">
	
		<xsl:text disable-output-escaping="yes">
		&lt;attribute name="</xsl:text>
	
		<xsl:value-of select="name()"/>
	
		<!-- =<xsl:value-of select="."/> -->

		<xsl:text disable-output-escaping="yes">"/&gt;</xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>






	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

    

    
    
    
    <xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>

	
	
	






</xsl:stylesheet>
