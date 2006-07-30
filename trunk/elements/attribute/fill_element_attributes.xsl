<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
       

    <!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>
   
	
	<xsl:template match="attribute">
				
				
				
		<!-- labely polozek-->
		
		<xsl:variable name="label_cat">
			<xsl:choose>
			
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:text>Kategorie</xsl:text>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:text>Categories</xsl:text>
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
		
		<xsl:variable name="label_misval">
			<xsl:choose>
			
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:text>Chybějící hodnoty</xsl:text>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:text>Missing values</xsl:text>
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->


				
				
				
				
				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				<element_attributes>
				
		
		
				<xsl:apply-templates select="@*"/>
				
				
				<xsl:element name="attribute">
					<xsl:attribute name="name">
						<xsl:value-of select="$label_cat" />
					</xsl:attribute>
					
					<xsl:attribute name="value">
  						<xsl:apply-templates select="ctgr" /> 
  					</xsl:attribute>
  				</xsl:element>
  				
  				
  				<xsl:element name="attribute">
					<xsl:attribute name="name">
						<xsl:value-of select="$label_misval" />
					</xsl:attribute>
					
					<xsl:attribute name="value">
  						<xsl:apply-templates select="missing_value" /> 
  					</xsl:attribute>
  				</xsl:element>
  				

				<xsl:text disable-output-escaping="yes">
				</xsl:text>
				</element_attributes>
	</xsl:template>

	
	
	
	
	
	
	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">


			<!-- labely polozek-->
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
			<!-- end of: labely polozek-->




	
					<xsl:text disable-output-escaping="yes">
					</xsl:text>
		
		
					<attribute name="{name()}" value="{.}" label="{$label}" />
	</xsl:template>
	<!-- vypise vsechny atributy -->







	<!-- vypise seznam kategorii-->
	<xsl:template match="ctgr">
	
    	<xsl:if test="position()!=1">
    		<xsl:text disable-output-escaping="no">; </xsl:text> 
    	</xsl:if>
    	<xsl:value-of select="@name" /> 
    
    </xsl:template>




	<!-- vypise kategorii s chybejici hodnotou-->
    <xsl:template match="missing_value">
    	
    	<xsl:if test="position()!=1">
    		<xsl:text disable-output-escaping="no">; </xsl:text> 
    	</xsl:if>
    	
    	<xsl:value-of select="@name" /> 
    </xsl:template>




</xsl:stylesheet>
