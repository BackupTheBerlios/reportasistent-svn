<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
  
  
   
    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>
       




<!-- ================= TEMPLATE ============================== -->


	
	<xsl:template match="/active_list">		
		<xsl:text disable-output-escaping="yes">

&lt;dialog_data&gt;
	</xsl:text>				

		<xsl:apply-templates select="node()[position()=1]" mode="attributes"/>





		<xsl:text disable-output-escaping="yes">
	&lt;values&gt;</xsl:text>				
	

		<xsl:apply-templates select="node()" mode="values"/>

		<xsl:text disable-output-escaping="yes">
	&lt;/values&gt;
		</xsl:text>				




		<xsl:text disable-output-escaping="yes">
&lt;/dialog_data&gt;
		</xsl:text>				
	</xsl:template>

	

<!-- ================= TEMPLATE ============================== -->	



	<!-- vypise atributy -->
	<xsl:template match="node()" mode="attributes">		

	<attributes>
		

		<xsl:apply-templates select="@*" mode="attributes"/>



<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<attribute name="categories_frequency"/>
<xsl:text disable-output-escaping="yes">
		</xsl:text>
		<attribute name="missing_values"/>



<xsl:text disable-output-escaping="yes">
	</xsl:text>				
	</attributes>


	</xsl:template>
	

<!-- ================= TEMPLATE ============================== -->


	<!-- vypise vsechny atributy -->
	<xsl:template match="@*" mode="attributes">
	
	
		<!-- nastaveni jazyka - labely-->
		
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Databáze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datová matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='attr_name'">
								<xsl:text>Jméno atributu</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='creation'">
								<xsl:text>Zdrojový sloupec</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_count'">
								<xsl:text>Počet kategorií</xsl:text>
							</xsl:when>
							
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='attr_name'">
								<xsl:text>Attribute name</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='creation'">
								<xsl:text>Source column</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='ctgr_count'">
								<xsl:text>Count of categories</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>

		<!-- nastaveni jazyka - labely-->
		
		
	
	
	
	
		<xsl:element name="attribute">
		
			<xsl:attribute name="name"><xsl:value-of select="name()"/></xsl:attribute>
			<xsl:attribute name="label"><xsl:value-of select="$label"/></xsl:attribute>
	
		</xsl:element>
	

	</xsl:template>



<!-- ================= TEMPLATE ============================== -->


	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<xsl:text disable-output-escaping="yes">categories_frequency="</xsl:text>
		<xsl:apply-templates select="ctgr" mode="values"/>
		<xsl:text disable-output-escaping="yes">" </xsl:text>
		
		<xsl:text disable-output-escaping="yes">missing_values="</xsl:text>
		<xsl:apply-templates select="missing_value" mode="values"/>
		<xsl:text disable-output-escaping="yes">"</xsl:text>

		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>


<!-- ================= TEMPLATE ============================== -->


	<!-- naplni hodnotu pro categories -->
	<xsl:template match="ctgr" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@name"/>
		<xsl:text disable-output-escaping="no"> (</xsl:text>
		<xsl:value-of select="@freq"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	<!-- naplni hodnotu pro missing_values -->
	<xsl:template match="missing_value" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:value-of select="@name"/>
	</xsl:template>



<!-- ================= TEMPLATE ============================== -->


	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
